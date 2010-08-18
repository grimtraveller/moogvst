#ifndef BASIC_BLOCKS_H
#define BASIC_BLOCKS_H
#include <vector>
using namespace std;

/*
 *
 * Essa é a classe base, todos os blocos devem derivar dela
 *
 */
class BasicBlock {
	public:
		BasicBlock(int numberOfInputs);
		void setInput(int i, BasicBlock * block);

		/*
		 * Esse método deve retornar a próxima saída (amostra)
		 * do bloco.
		 */
		virtual float getNextValue() = 0;
		/*
		 * Reseta os parâmetros do bloco.
		 */
		virtual void resetBlock(void);
		/*
		 * Preenche o array output com amostras.
		 */
		virtual void generateSamples(float * output, int sampleNum);
	protected:
		vector<BasicBlock *> inputs;
};
/*
 * Somador
 *
 * Número de entradas: Configurável através do construtor
 */
class Adder: public BasicBlock {
	public:
		Adder(int numberOfInputs);
		~Adder();

		float getNextValue();
};

/*
 * Multiplexador
 *
 * Número de entradas: Configurável através do construtor
 */
class Multiplexer: public BasicBlock {
	public:
		Multiplexer(int numberOfInputs, int selectedInput = 0);
		~Multiplexer();
		/*
		 * Seleciona a i-ésima entrada.
		 */
		void setSelectedInput(int i);
		int getSelectedInput();
		/*
		 * Obtém a saída do bloco selecionado
		 */
		float getNextValue();
	private:
		int selectedInput;
};

/*
 * Uma constante numérica. Esse bloco não tem entradas, ele apenas
 * retorna um valor fixo ao chamar getNextValue
 *
 * Número de entradas: 0
 */
class Number: public BasicBlock {
	public:
		Number(float number);
		~Number();
		float getNextValue();
		void setNumber(float number);
		float getNumber(void);
	private:
		float number;
};

enum wavetypes {
	TRIG, SAWTRIG, SAW, SQUARE, WIDERECT, NARROWRECT,
};

typedef enum wavetypes wavetype_t;

class Waveforms {
	private:
		static vector<float> * trig;
		static vector<float> * sawtrig;
		static vector<float> * saw;
		static vector<float> * square;
		static vector<float> * widerect;
		static vector<float> * narrowrect;
	public:
		static void initializeWaves(int length, int extraPoints);
		static void deleteWaves();
		static vector<float> * getWaveform(wavetype_t wave);
};

/*
 * Um oscilador de table lookup. É possível
 * configurar a forma de onda utilizada. Veja a enum
 * wavetypes e o método setWavetable
 *
 * Número de entradas: 2 (Frequência e Amplitude)
 */
class Oscil: public BasicBlock {
	public:
		Oscil();
		Oscil(wavetype_t wave);

		void setFrequencyInput(BasicBlock * block);
		void setAmplitudeInput(BasicBlock * block);
		void setWavetable(wavetype_t wave);
		void setWavetable(vector<float> & table);
		float getNextValue();
		void reset_block(void);
	private:
		float cubic_interpolation(float phase)const;
		float linear_interpolation(float phase)const;
		vector<float>& table;
		float increment;
		float previous_phase;
};

enum noisetype {
	WHITE,
	PINK
};
typedef enum noisetype noisetype_t;

/*
 * Gerador de ruído branco ou rosa.
 *
 * Número de entradas: 0
 */
class Noise: public BasicBlock {
	public:
		Noise();
		void setType(noisetype_t type);
		noisetype_t getType();
		float getNextValue();
	private:
		noisetype_t noise_type;
		float (*noiseGenerator)();
};

/*
 * Filtro do Moog, com frequencia controlada e fator de qualidade.
 *
 * Numero de entradas: 2, o sinal a ser filtrado e a frequencia de corte
 * pra construir precisa do fator de qualidade, mas pode ser mudado depois.
 */
class Filter: public BasicBlock{
	public:
		Filter(float quality);
		void setInputSignal(BasicBlock * block);
		void setFrequencyInput(BasicBlock * block);
		void setQuality(float quality);
		float getNextValue();
	private:
		float CutOffFrequency;
		float Quality;
		float previousOutput;
};
#endif 
