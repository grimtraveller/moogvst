#include "audioeffectx.h"
#include "Moog.h"

#define NUM_PARAMS 1
enum {
// Parameters Tags
	oscil1Waveform = 0,
	oscil1Amp,
	oscil1Range,
	oscil1Freq,
	oscil1ON
};

class MoogPlugin : public AudioEffectX {
public:
	MoogPlugin(audioMasterCallback audioMaster);
	~MoogPlugin();
	void processReplacing(float **inputs, float **outputs, VstInt32 sampleFrames);
	double freqTable[128];
	VstInt32 processEvents (VstEvents* ev);
private:
	VstInt32 currentNote;
	VstInt32 currentVelocity;
	VstInt32 currentDelta;
	bool noteIsOn;
	void noteOn (VstInt32 note, VstInt32 velocity, VstInt32 delta);
	void noteOff ();
	Moog * moog;

	/*
	 * Parâmetros
	 *
	 */
	virtual void setParameter (VstInt32 index, float value);
	virtual float getParameter (VstInt32 index);
	virtual void getParameterLabel (VstInt32 index, char* label);
	virtual void getParameterDisplay (VstInt32 index, char* text);
	virtual void getParameterName (VstInt32 index, char* text);
};