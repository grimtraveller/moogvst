#include "MoogPlugin.h"

/*
 * 
 * Funções auxiliares
 *
 */
static wavetype_t float2wavetype(float value) {
	if (value <= 0.16) {
		return TRIG;
	}
	else if (value <= 0.32) {
		return SAWTRIG;
	}
	else if (value <= 0.48) {
		return SAW;
	}
	else if (value <= 0.64) {
		return SQUARE;
	}
	else if (value <= 0.80) {
		return WIDERECT;
	}
	return NARROWRECT;
}

static float wavetype2float(wavetype_t type) {
	switch (type) {
	case TRIG:
		return 0.0;
	case SAWTRIG:
		return 0.32;
	case SAW:
		return 0.48;
	case SQUARE:
		return 0.64;
	case WIDERECT:
		return 0.80;
	case NARROWRECT:
		return 1.00;
	}
}

static char *wavetypeStrings[] = {"Trig","SawTrig","Saw","Square","WRect","Narrow"};


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
	noteIsOn = false;
	currentDelta = currentNote = currentVelocity = 0;
	moog = new Moog();
	moog->setNoiseON(false);
	moog->setFilterON(false);
	moog->setMasterAmp(1.0f);
	moog->setOscil2ON(false);
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

/*
 * Parâmetros
 */

void MoogPlugin::setParameter(VstInt32 index, float value){
	switch (index) {
	case oscil1Waveform:
		moog->setOscil1Waveform(float2wavetype(value));
	}
}

float MoogPlugin::getParameter(VstInt32 index) {
	switch (index) {
	case oscil1Waveform:
		return wavetype2float(moog->getOscil1Waveform());
	}
}

void MoogPlugin::getParameterLabel (VstInt32 index, char* label){
	switch (index) {
	case oscil1Waveform:
		vst_strncpy (label, "Shape", kVstMaxParamStrLen);
		break;
	}
}

void MoogPlugin::getParameterDisplay (VstInt32 index, char* text){
	switch (index) {
	case oscil1Waveform:
		vst_strncpy (text, wavetypeStrings[moog->getOscil1Waveform()], kVstMaxParamStrLen);
		break;

	}
}

void MoogPlugin::getParameterName (VstInt32 index, char* text){
	switch (index) {
	case oscil1Waveform:
		vst_strncpy (text, "Oscil 1 Wave", kVstMaxParamStrLen);	break;
	}
}

