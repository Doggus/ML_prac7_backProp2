#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct IOdata
{
    float input1;
    float input2;
    float input3;

    float output;

    IOdata(float i1, float i2, float i3, float o)
    {
        input1 = i1;
        input2 = i2;
        input3 = i3;
  
        output = o;
    }
};

struct neuron
{
	float nodeValue;
	vector<float> weights;
	
	neuron(const float &nv, const vector<float> &w)
	{
		nodeValue = nv;
		weights = w;
	}

	void sigmoid()
	{
		nodeValue = 1/(1 + exp(-nodeValue));
	}

	void calculateLayerValue(const vector<float> &inputs, const vector<float> &weights)
	{
		nodeValue = 0;
		if (inputs.size() == weights.size())
		{
			for (int i = 0; i < inputs.size(); ++i)
			{
				nodeValue += inputs[i] * weights[i];
			}

			sigmoid();

		}
		else
		{
			cout << "Neuron value cannot be calculated" << endl;
			return;
		}
		
	}
};

float getRandomFloat(float a, float b) 
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int main()
{
   //Vector making up the 3 parity XOR table
   vector<IOdata> XORdata;
   XORdata.push_back(IOdata(0,0,0,0));
   XORdata.push_back(IOdata(0,0,1,1));
   XORdata.push_back(IOdata(0,1,0,1));
   XORdata.push_back(IOdata(0,1,1,0));
   XORdata.push_back(IOdata(1,0,0,1));
   XORdata.push_back(IOdata(1,0,1,0));
   XORdata.push_back(IOdata(1,1,0,0));
   XORdata.push_back(IOdata(1,1,1,1));
   
   //Each XOR entry makes up one neural network with the 3 input float making up the inputLayer and the desired output for those inputs
   //GOAL: to find the correct weights of the connections between the input, hidden and output layers 
   //METHOD: create a neural network for each entry in the 3 parity XOR table
   //Each input node will have 3 weights, each corresponding to 3 different hidden layer nodes
   //Weights are intialised to random float betwen -1 and 1 (they are not known in the beginning)
   //(initial weight doesn't matter - it will change as program finds the true weight given the desired output)

   //According to sasha, you should probably always have a bias node unless instructed otherwise
   //when back propogating i dont think initial weight bias means that much, because it gets updated later anyway 
   //But if just forward passing, I can see how that would effect the neural network 

   //FORWARD PASS:
   for (int i = 0; i < XORdata.size(); ++i)
   {
   	   cout << "FORWARD PASS: " << "Entry " << i << " in XOR table" << endl;
	   cout << "" << endl;

	   vector<neuron> inputLayer = 
		{
			neuron(XORdata[i].input1, vector<float> {getRandomFloat(-1,1), getRandomFloat(-1,1), getRandomFloat(-1,1)}),
			neuron(XORdata[i].input2, vector<float> {getRandomFloat(-1,1), getRandomFloat(-1,1), getRandomFloat(-1,1)}),
			neuron(XORdata[i].input3, vector<float> {getRandomFloat(-1,1), getRandomFloat(-1,1), getRandomFloat(-1,1)}),
			//Bias neuron: always has node value of 1, its weights are the bias (they are manually chosen)
			neuron(1.0f, vector<float> {0.1f, -0.2, 0.3f})
		};

		//vectors of all input neuron float values and the their weights that point to each hidden neuron (and the bias)
		vector<float> inputValues {inputLayer[0].nodeValue, inputLayer[1].nodeValue, inputLayer[2].nodeValue, inputLayer[3].nodeValue};
		//weights pointing to hidden node 1
		vector<float> weights1 {inputLayer[0].weights[0], inputLayer[1].weights[0], inputLayer[2].weights[0], inputLayer[3].weights[0]};
		//weights pointing to hidden node 2
		vector<float> weights2 {inputLayer[0].weights[1], inputLayer[1].weights[1], inputLayer[2].weights[1], inputLayer[3].weights[1]};
		//weights pointing to hidden node 3
		vector<float> weights3 {inputLayer[0].weights[2], inputLayer[1].weights[2], inputLayer[2].weights[2], inputLayer[3].weights[2]};

		//default node value to 0 before we calculate its value (initial value is arbitrary), weight once again initialised to random float
		//Neural network converges to one output from the hidden layer, thus hidden nodes will have one weight pointing to the out put node
		neuron hiddenNeuron1 = neuron(0.0f, vector<float> {getRandomFloat(-1,1)});
		neuron hiddenNeuron2 = neuron(0.0f, vector<float> {getRandomFloat(-1,1)});
		neuron hiddenNeuron3 = neuron(0.0f, vector<float> {getRandomFloat(-1,1)});
		//hidden bias node (manually assigned a weight) [always has node value of 1]
		neuron hiddenBias = neuron(1.0f, vector<float> {0.1f});
		//instantiate output empty neuron 
		neuron outputNeuron = neuron(0, vector<float> {});
		float targetOutput = XORdata[i].output;
		//learning rate is a value to help determine how much weights will be adjusted as program learns (it is manually adjusted my me) [between 0 and 1]
		//I THINK as the value is smaller it results in more accurate but slower changes, and as it gets larger it results in less accurate but faster changes 
		float learningRate = 0.5;
		//initialsing 
		float meanSquaredError = 1;

		bool complete = false;
		int count = 0;

		while(!complete)
    	{
	    	if ((meanSquaredError <= 0.3f && meanSquaredError >= -0.3f) || count == 5)
	    	{
	    		complete = true;
	    		count = 0;
	    		cout << "Results of the final forward and back propagation of neural network for XOR table entry " << i << endl;
	    		cout << "" << endl;
	    	}
	    	else
	    	{
	    		cout << "XOR table Entry " << i << ": Forward Passing " << count << endl;
	    		cout << "XOR table Entry " << i << ": Back Propagating " << count << endl;
	    		cout << "" << endl;
	    	}

	    	if (complete == true)
	    	{
	    		cout << "Forward Pass: layer 1 weights: " << endl;
				cout << "I1: W1: " << weights1[0] << endl;
				cout << "I1: W2: " << weights2[0] << endl;
				cout << "I1: W3: " << weights3[0] << endl;
				cout << "" << endl;
				cout << "I2: W1: " << weights1[1] << endl;
				cout << "I2: W2: " << weights2[1] << endl;
				cout << "I2: W3: " << weights3[1] << endl;
				cout << "" << endl;
				cout << "I3: W1: " << weights1[2] << endl;
				cout << "I3: W2: " << weights2[2] << endl;
				cout << "I3: W3: " << weights3[2] << endl;
				cout << "" << endl;
				cout << "Ibias: W1: " << weights1[3] << endl;
				cout << "Ibias: W2: " << weights2[3] << endl;
				cout << "Ibias: W3: " << weights3[3] << endl;
				cout << "" << endl;
	    	}

			//calculate float values for hidden node 1
			hiddenNeuron1.calculateLayerValue(inputValues, weights1);

			//calculate float values for hidden node 2
			hiddenNeuron2.calculateLayerValue(inputValues, weights2);
		
			//calculate float values for hidden node 3
			hiddenNeuron3.calculateLayerValue(inputValues, weights3);

			if (complete == true)
	    	{
				cout << "Forward pass: HiddenNeuron1: " << hiddenNeuron1.nodeValue << endl;
				cout << "Forward pass: HiddenNeuron2: " << hiddenNeuron2.nodeValue << endl;
				cout << "Forward pass: HiddenNeuron3: " << hiddenNeuron3.nodeValue << endl;
				cout << "Forward pass: HiddenBias: " << hiddenBias.nodeValue << endl;
				cout << "" << endl;
			}

			//vectors of all hidden neuron float values and the their weights that point to the output neuron
			vector<float> hiddenValues {hiddenNeuron1.nodeValue, hiddenNeuron2.nodeValue, hiddenNeuron3.nodeValue, hiddenBias.nodeValue};
			//weights that point to the output node 
			vector<float> hiddenWeights {hiddenNeuron1.weights[0], hiddenNeuron2.weights[0], hiddenNeuron3.weights[0], hiddenBias.weights[0]};

			if (complete == true)
	    	{
				cout << "Forward Pass: layer 2 weights: " << endl;
				cout << "H1: W: " << hiddenWeights[0] << endl;
				cout << "H2: W: " << hiddenWeights[1] << endl;
				cout << "H3: W: " << hiddenWeights[2] << endl;
				cout << "HBias: W: " << hiddenWeights[3] << endl;
				cout << "" << endl;
			}

			//calculate float values for output node
			outputNeuron.calculateLayerValue(hiddenValues, hiddenWeights);

			if (complete == true)
	    	{
				cout << "Forward pass: outputNeuron: " << outputNeuron.nodeValue << endl;
				cout << "" << endl;
			}

			//BACK PROPOGATION:
			if (complete == true)
	    	{
				cout << "BACK PROPOGATION: " << "Entry " << i << " in XOR table" << endl;
			    cout << "" << endl;
			}

			//calculate output error values for back propagation
			float outputError = outputNeuron.nodeValue*(1-outputNeuron.nodeValue)*(targetOutput-outputNeuron.nodeValue);

			if (complete == true)
	    	{
				cout << "outputError: " << outputError << endl;
				cout << "" << endl;
			}

			//Work out new weights in layer 2 (between hidden and output node):

			hiddenWeights[0] += learningRate*outputError*hiddenNeuron1.nodeValue;
			hiddenWeights[1] += learningRate*outputError*hiddenNeuron2.nodeValue;
			hiddenWeights[2] += learningRate*outputError*hiddenNeuron3.nodeValue;
			//update weights of the hidden bias node
			hiddenWeights[3] += learningRate*outputError*hiddenBias.nodeValue;

			if (complete == true)
	    	{
				cout << "New layer 2 weights (learning rate(n) = " << learningRate << "): " << endl;
				cout << "H1: W: " << hiddenWeights[0] << endl;
				cout << "H2: W: " << hiddenWeights[1] << endl;
				cout << "H3: W: " << hiddenWeights[2] << endl;
				cout << "HBias: W: " << hiddenWeights[3] << endl;
				cout << "" << endl;
			}

			//calculate hidden error values for back propagation
			float hiddenError1 = hiddenNeuron1.nodeValue*(1-hiddenNeuron1.nodeValue)*( (hiddenWeights[0]*outputError) );
			float hiddenError2 = hiddenNeuron2.nodeValue*(1-hiddenNeuron2.nodeValue)*( (hiddenWeights[1]*outputError) );
			float hiddenError3 = hiddenNeuron3.nodeValue*(1-hiddenNeuron3.nodeValue)*( (hiddenWeights[2]*outputError) );
			float hiddenBiasError = hiddenBias.nodeValue*(1-hiddenBias.nodeValue)*( (hiddenWeights[3]*outputError) );

			if (complete == true)
	    	{
				cout << "hiddenError1: " << hiddenError1 << endl;
				cout << "hiddenError2: " << hiddenError2 << endl;
				cout << "hiddenError3: " << hiddenError3 << endl;
				cout << "hiddenBiasError: " << hiddenBiasError << endl;
				cout << "" << endl;
			}

			//Now that we have the hidden node error values we work out the new weights in the first layer (between input and hidden nodes):

			//weights pointing to first hidden Node (top of the layer) [Each weight belongs to a different input layer node]
			weights1[0] += learningRate*hiddenError1*inputValues[0];
			weights1[1] += learningRate*hiddenError1*inputValues[1];
			weights1[2] += learningRate*hiddenError1*inputValues[2];

			//weights pointing to second hidden node
			weights2[0] += learningRate*hiddenError2*inputValues[0];
			weights2[1] += learningRate*hiddenError2*inputValues[1];
			weights2[2] += learningRate*hiddenError2*inputValues[2];

			//weights pointing to third hidden node
			weights3[0] += learningRate*hiddenError3*inputValues[0];
			weights3[1] += learningRate*hiddenError3*inputValues[1];
			weights3[2] += learningRate*hiddenError3*inputValues[2];

			//update weights of bias node in the input layer
			weights1[3] += learningRate*hiddenBiasError*inputValues[3]; // inputValues[3] = 1
			weights2[3] += learningRate*hiddenBiasError*inputValues[3];
			weights3[3] += learningRate*hiddenBiasError*inputValues[3];

			if (complete == true)
	    	{
				cout << "New layer 1 weights (learning rate(n) = " << learningRate << "): " << endl;
				cout << "I1: W1: " << weights1[0] << endl;
				cout << "I1: W2: " << weights2[0] << endl;
				cout << "I1: W3: " << weights3[0] << endl;
				cout << "" << endl;
				cout << "I2: W1: " << weights1[1] << endl;
				cout << "I2: W2: " << weights2[1] << endl;
				cout << "I2: W3: " << weights3[1] << endl;
				cout << "" << endl;
				cout << "I3: W1: " << weights1[2] << endl;
				cout << "I3: W2: " << weights2[2] << endl;
				cout << "I3: W3: " << weights3[2] << endl;
				cout << "" << endl;
				cout << "Ibias: W1: " << weights1[3] << endl;
				cout << "Ibias: W2: " << weights2[3] << endl;
				cout << "Ibias: W3: " << weights3[3] << endl;
				cout << "" << endl;
			}

			//The mean-squared error should be 0 or very close to 0 to conclude that the network has learnt the XOR function correctly
			meanSquaredError = pow(outputNeuron.nodeValue - targetOutput, 2);

			if (complete == true)
	    	{
				cout << "Mean Squared Error: " << meanSquaredError << endl;
				cout << "" << endl;
				cout << "--------------------------------------------------" << endl;
				cout << "" << endl;
			}

			count++;
   		}

   }

	return 0;
}