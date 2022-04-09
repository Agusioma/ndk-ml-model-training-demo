#include <jni.h>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <random>
#include <math.h>

using namespace std;

/*	vector<vector<string>> content;
	vector<string> row;
	string line, word;
	int noOfRows;
	int noOfColumns = 13;
	int noOfIterations = 1;

	int* shuffle_indices(int arr[], int n);
	vector<double> updateWeightsAndBias(int noOfIterations, int trainData[5][14]);

void processDataset(string fname){
	fstream file (fname, ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while(getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout<<"Could not open the file\n";

	/*for(int i=0;i<content.size();i++)
	{
		for(int j=0;j<content[i].size();j++)
		{
			cout<<content[i][j]<<" ";
		}3
		cout<<"\n";
	}*/
	/*noOfRows = content.size()-1;
	noOfColumns = content[0].size();
	int dataset[5][14];
	int datasetSize = content.size();
	//minusing 1 because of the header row values(age, sex etc)
	int indices[4];

	for (int i = 0; i < 5; i++) {
      indices[i] =  i + 1;
    }

	int* shuffled_indices = shuffle_indices(indices, 4);

	for (int i = 0; i < noOfRows; i++) {
      for(int j = 0; i < noOfColumns; j++){
      //starting from the second row to the last row
      /*since we are accesing the CSV sequentially, we skip the first row and access the next index.
      the same 'next index access' is replicated for the rest*/
       /* dataset[shuffled_indices[i]][noOfColumns]=stoi(content[i+1][j]);
      }
    }

	//return dataset;
	updateWeightsAndBias(noOfIterations, dataset);
}

int passFunc(int a[][2]){
    return a[0][1];
}

int* shuffle_indices(int arr[], int n){

    // To obtain a time-based seed
    unsigned seed = 7;

    // Shuffling our array
    shuffle(arr, arr + n,
            default_random_engine(seed));

    // Printing our array
    /*for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;*/
  /*  return arr;
}

vector<double> updateWeightsAndBias(int noOfIterations){
                double row_pred_diff = 0.0;
                                double total_diff = 0.0;
                                double feature_weight[noOfColumns] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                                double total_feature_weight[noOfColumns] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                                double weight_derivative[noOfColumns] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                                double bias_derivative = 0.0;
                                double W[noOfColumns] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                                double bias = 0.0;
                                vector<double> vWB;

                                //train set
                                double X_train[9][13] = {
                                {57.0,0.0,0.0,140.0,241.0,0.0,1.0,123.0,1.0,0.2,1.0,0.0,3.0},
                                {45.0,1.0,3.0,110.0,264.0,0.0,1.0,2.0,0.0,1.2,1.0,0.0,3.0},
                                {68.0,1.0,0.0,144.0,13.0,1.0,1.0,141.0,0.0,3.4,1.0,2.0,3.0},
                                {57.0,1.0,0.0,80.0,1.0,0.0,1.0,115.0,1.0,1.2,1.0,1.0,3.0},
                                {57.0,0.0,1.0,0.0,236.0,0.0,0.0,174.0,0.0,0.0,1.0,1.0,2.0},
                                {61.0,1.0,0.0,140.0,207.0,0.0,0.0,8.0,1.0,1.4,2.0,1.0,3.0},
                                {46.0,1.0,0.0,140.0,311.0,0.0,1.0,120.0,1.0,1.8,1.0,2.0,3.0},
                                {62.0,1.0,1.0,128.0,208.0,1.0,0.0,140.0,0.0,0.0,2.0,0.0,2.0},
                                {62.0,1.0,1.0,128.0,208.0,1.0,0.0,140.0,0.0,0.0,2.0,0.0,2.0}};

                                //labels
                                double Y[noOfRows] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0};


                                for (int l = 0; l < noOfIterations; l++){
                                        for (int i = 0; i < noOfRows; i++){
                                        double Wx = 0.0;
                                            //computing W.x
                                            for (int j = 0; j < noOfColumns; j++){
                                                Wx = W[j] * X_train[i][j];
                                            }
                                            //computing (σ(W.x) + b) - Y
                                            row_pred_diff = (1/(1 + exp(-(Wx+bias))))-Y[i];
                                            for (int k = 0; k < noOfColumns; k++){
                                                //computing (σ(W.x) + b) - Y × x(i)
                                                feature_weight[k] = row_pred_diff * X_train[i][k];
                                                //summation(Σ) of each feature weight
                                                total_feature_weight[k] += feature_weight[k];
                                            }
                                            //summation(Σ) of predictions
                                            total_diff += row_pred_diff;

                                        }
                                    //updating the weights for each feature
                                    for (int z = 0; z < noOfColumns; z++){
                                            //computing the average of the weights(1/m)
                                            weight_derivative[z] = total_feature_weight[z]/noOfRows;
                                            W[z] = W[z] - 0.1 * weight_derivative[z];
                                            //storing the values in a vector
                                            vWB.push_back(W[z]);
                                    }

                                        //calculating the bias
                                        bias_derivative = total_diff/noOfRows;
                                        bias = bias - 0.1 * bias_derivative;
                                        vWB.push_back(bias);
                                }
                            return vWB;

        }*/
class CPPLogisticRegression{
    public:
        //method for updating the weights and bias
        vector<double> updateWeightsAndBias(int noOfIterations, int noOfRows, int noOfColumns);
        //method for the prediction
        double predict(vector<double> vW, double* X_train_test);
};

        vector<double> CPPLogisticRegression::updateWeightsAndBias(int noOfIterations, int noOfRows, int noOfColumns){
                double row_pred_diff = 0.0;
                double total_diff = 0.0;
                double feature_weight[noOfColumns] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                double total_feature_weight[noOfColumns] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                double weight_derivative[noOfColumns] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                double bias_derivative = 0.0;
                double W[noOfColumns] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                double bias = 0.0;
                vector<double> vWB;

                //train set
                double X_train[noOfRows][noOfColumns] = {
                {57.0,0.0,0.0,140.0,241.0,0.0,1.0,123.0,1.0,0.2,1.0,0.0,3.0},
                {45.0,1.0,3.0,110.0,264.0,0.0,1.0,2.0,0.0,1.2,1.0,0.0,3.0},
                {68.0,1.0,0.0,144.0,13.0,1.0,1.0,141.0,0.0,3.4,1.0,2.0,3.0},
                {57.0,1.0,0.0,80.0,1.0,0.0,1.0,115.0,1.0,1.2,1.0,1.0,3.0},
                {57.0,0.0,1.0,0.0,236.0,0.0,0.0,174.0,0.0,0.0,1.0,1.0,2.0},
                {61.0,1.0,0.0,140.0,207.0,0.0,0.0,8.0,1.0,1.4,2.0,1.0,3.0},
                {46.0,1.0,0.0,140.0,311.0,0.0,1.0,120.0,1.0,1.8,1.0,2.0,3.0},
                {62.0,1.0,1.0,128.0,208.0,1.0,0.0,140.0,0.0,0.0,2.0,0.0,2.0},
                {62.0,1.0,1.0,128.0,208.0,1.0,0.0,140.0,0.0,0.0,2.0,0.0,2.0}};

                //labels
                double Y[noOfRows] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0};


                for (int l = 0; l < noOfIterations; l++){
                        for (int i = 0; i < noOfRows; i++){
                        double Wx = 0.0;
                            //computing W.x
                            for (int j = 0; j < noOfColumns; j++){
                                Wx = W[j] * X_train[i][j];
                            }
                            //computing (σ(W.x) + b) - Y
                            row_pred_diff = (1/(1 + exp(-(Wx+bias))))-Y[i];
                            for (int k = 0; k < noOfColumns; k++){
                                //computing (σ(W.x) + b) - Y × x(i)
                                feature_weight[k] = row_pred_diff * X_train[i][k];
                                //summation(Σ) of each feature weight
                                total_feature_weight[k] += feature_weight[k];
                            }
                            //summation(Σ) of predictions
                            total_diff += row_pred_diff;

                        }
                    //updating the weights for each feature
                    for (int z = 0; z < noOfColumns; z++){
                            //computing the average of the weights(1/m)
                            weight_derivative[z] = total_feature_weight[z]/noOfRows;
                            W[z] = W[z] - 0.1 * weight_derivative[z];
                            //storing the values in a vector
                            vWB.push_back(W[z]);
                    }

                        //calculating the bias
                        bias_derivative = total_diff/noOfRows;
                        bias = bias - 0.1 * bias_derivative;
                        vWB.push_back(bias);
                }
            return vWB;

        }

        double CPPLogisticRegression::predict(vector<double> vW, double* X_train_test){
            static double predictions;
            double Wx_test = 0.0;
                //computing σ(W.x)
                for (int j = 0; j < 13; j++){
                    Wx_test += (vW[j] * X_train_test[j]);
                }
                //adding the bias term
                predictions = 1/(1 + exp(-(Wx_test + vW.back())));
                //making the prediction
                if(predictions>0.5){
                    predictions = 1.0;
                }else{
                    predictions = 0.0;
                }
            return predictions;
        }


extern "C" JNIEXPORT jstring JNICALL
Java_com_terrence_heartndk_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_terrence_heartndk_MainActivity_pathFromJNI(
        JNIEnv* env,
        jobject, /* this */
        jstring path
        ) {

        //const char* string = path;
       const char *name = env->GetStringUTFChars(path, 0);
        std::string str = name;
    //std::string hello = "Hello from C++";
    str = str+"/heart.csv";
    //processDataset(str);
    //string tt = checkFirst(str);
    /*int array[2][2] = {
    {0,2},
    {1,4}
    };
    passFunc(array);
    string g = to_string(passFunc(array));*/
    return env->NewStringUTF(str.c_str());
}

