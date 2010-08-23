#include "audioeffectx.h"
#include "Moog.h"

#define NUM_PARAMS 0

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
};