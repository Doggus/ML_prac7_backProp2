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

    float weight1;
    float weight2;
    float weight3;

    float output;

    IOdata(float i1, float i2, float i3, float o)
    {
        input1 = i1;
        input2 = i2;
        input3 = i3;

        //intialised to random float betwen -1 and 1 
        //(initial weight doesn't matter - it will change as program finds its true weight)
        weight1 = getRandomFloat(-1,1);
        weight2 = getRandomFloat(-1,1);
        weight3 = getRandomFloat(-1,1);

        output = o;
    }
};

float getRandomFloat(float a, float b) 
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

bool learningAlgorithm(IOdata data, vector<float> weights, int correctValueCount, const string type)
{

   float weightedSum = 0;
   //3 parity XOR, 8 rows in the table (check question on vula)
   for (int i = 0; i < 8; ++i)
   {
       weightedSum += (data.input1 * weights[0]) + (data.input2 * weights[1]) + (data.input3 * weights[2]);
   }

   //Apply the weighted sum to the correct Activation Function.
   //Using the sigmoid activation function 
   float thresholdValue = sigmoid(weightedSum);

   // if errorValue = 0 threshold value is equal to true output
   float errorValue = data.output - thresholdValue;
   bool isEqual;

   if (errorValue == 0)
   {
        isEqual = true;
   }
   else
   {
   		isEqual = false;
   }

   cout << data.input1 << type << data.input2 << " = " << thresholdValue << " true output is: " << data.output << endl;

   //arbitrary value between 0 and 1
   float learningRate = 0.5f;

   if (!isEqual)
   {
       cout << "Therefore: change weights, errorValue = " << errorValue << endl;

       weights.first += learningRate * errorValue * data.input1;
       weights.second += learningRate * errorValue * data.input2;

       correctValueCount = 0;

       return false;
   }

   ++correctValueCount;
   //return true if 4 in a row are correct
   return correctValueCount == 4;

}

float sigmoid(float nodeValue)
{
	nodeValue = 1/(1 + exp(-nodeValue));
	return nodeValue;
}

float calculateLayerValue(const vector<float> &inputs, const vector<float> &weights)
{
	int nodeValue = 0;

	if (inputs.size() == weights.size())
	{
		for (int i = 0; i < inputs.size(); ++i)
		{
			inputValue += inputs[i] * weights[i];
		}

		nodeValue = sigmoid(nodeValue);
		return nodeValue;
	}
	else
	{
		cout << "Node value cannot be calculated" << endl;
		return;
	}
	
}

int main()
{

   cout << "sup" << endl;

   vector<IOdata> XORdata;
   XORdata.push_back(IOdata(0,0,0,0));
   XORdata.push_back(IOdata(0,0,1,1));
   XORdata.push_back(IOdata(0,1,0,1));
   XORdata.push_back(IOdata(0,1,1,0));
   XORdata.push_back(IOdata(1,0,0,1));
   XORdata.push_back(IOdata(1,0,1,0));
   XORdata.push_back(IOdata(1,1,0,0));
   XORdata.push_back(IOdata(1,1,1,1));
   
   //intialised to random float betwen -1 and 1
   vector<float> weights;
   for (int i = 0; i < 4; ++i)
   {
       weights[i] = getRandomFloat(-1,1);
       weights.second = getRandomFloat(-1,1);
   }

	return 0;
}