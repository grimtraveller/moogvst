#include "MoogPlugin.h"

AudioEffect* createEffectInstance(audioMasterCallback audioMaster) {
	return new MoogPlugin(audioMaster);
}

MoogPlugin::MoogPlugin(audioMasterCallback audioMaster) : AudioEffectX(audioMaster, 0, NUM_PARAMS) {
	if (audioMaster) {
		setNumInputs (0);
		setNumOutputs (1);	
		canProcessReplacing ();
		isSynth ();
		setUniqueID(667);
	}
	suspend();
	double k = 1.059463094359;	// 12th root of 2
	double a = 6.875;	// a
	a *= k;	// b
	a *= k;	// bb
	a *= k;	// c, frequency of midi note 0
	for (int i = 0; i < 128; i++) {
		freqTable[i] = a;
		a *= k;
	}
	Waveforms::initializeWaves(1024,2);
	moog = new Moog();
	moog->setNoiseON(false);
	moog->setFilterON(true);
	moog->setMasterAmp(0.5f);
}

MoogPlugin::~MoogPlugin() {
	delete moog;
}

void MoogPlugin::processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames) {
	float* out1 = outputs[0];

	if (noteIsOn) {
		double baseFreq = freqTable[currentNote & 0x7f];
		
		if (currentDelta > 0)
		{
			if (currentDelta >= sampleFrames)	// future
			{
				currentDelta -= sampleFrames;
				return;
			}
			memset (out1, 0, currentDelta * sizeof (float));
			out1 += currentDelta;
			sampleFrames -= currentDelta;
			currentDelta = 0;
		}
		
		for (VstInt32 i = 0; i < sampleFrames; i++) {
			out1[i] = moog->getNextValue();
		}
	}						
	else{
		memset (out1, 0, sampleFrames * sizeof (float));
	}
}

VstInt32 MoogPlugin::processEvents (VstEvents* ev)
{
	for (VstInt32 i = 0; i < ev->numEvents; i++)
	{
		if ((ev->events[i])->type != kVstMidiType)
			continue;

		VstMidiEvent* event = (VstMidiEvent*)ev->events[i];
		char* midiData = event->midiData;
		VstInt32 status = midiData[0] & 0xf0;	// ignoring channel
		if (status == 0x90 || status == 0x80)	// we only look at notes
		{
			VstInt32 note = midiData[1] & 0x7f;
			VstInt32 velocity = midiData[2] & 0x7f;
			if (status == 0x80)
				velocity = 0;	// note off by velocity 0
			if (!velocity && (note == currentNote))
				noteOff ();
			else
				noteOn (note, velocity, event->deltaFrames);
		}
		else if (status == 0xb0)
		{
			if (midiData[1] == 0x7e || midiData[1] == 0x7b)	// all notes off
				noteOff ();
		}
		event++;
	}
	return 1;
}

void MoogPlugin::noteOn (VstInt32 note, VstInt32 velocity, VstInt32 delta) {
	currentNote = note;
	currentVelocity = velocity;
	currentDelta = delta;
	noteIsOn = true;
	moog->setInputFreq(freqTable[note]);
}

void MoogPlugin::noteOff () {
	noteIsOn = false;
}