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

class CPPLogisticRegression{
    public:
        //method for updating the weights and bias
        vector<double> updateWeightsAndBias(string fname);
        //method for the prediction
        double predict(vector<double> vW);
};

        vector<double> CPPLogisticRegression::updateWeightsAndBias(string fname){
                double row_pred_diff = 0.0;
                double total_diff = 0.0;
                double feature_weight[13] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                double total_feature_weight[13] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                double weight_derivative[13] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                double bias_derivative = 0.0;
                double W[13] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
                double bias = 0.0;
                vector<double> vWB;
                vector<vector<string>> content;
                vector<string> row;
                string line, word;

                //opening and reading the csv file
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

                //train set
                for (int l = 0; l < 50; l++){
                        for (int i = 1; i < content.size(); i++){
                        double Wx = 0.0;
                            //computing W.x
                            for (int j = 0; j < 13; j++){
                                Wx = W[j] * stoi(content[i][j]);
                            }
                            //computing (σ(W.x) + b) - Y
                            row_pred_diff = (1/(1 + exp(-(Wx+bias))))-stoi(content[i][13]);
                            for (int k = 0; k < 13; k++){
                                //computing (σ(W.x) + b) - Y × x(i)
                                feature_weight[k] = row_pred_diff * stoi(content[i][k]);
                                //summation(Σ) of each feature weight
                                total_feature_weight[k] += feature_weight[k];
                            }
                            //summation(Σ) of predictions
                            total_diff += row_pred_diff;

                        }
                    //updating the weights for each feature
                    for (int z = 0; z < 13; z++){
                            //computing the average of the weights(1/m)
                            weight_derivative[z] = total_feature_weight[z]/9;
                            W[z] = W[z] - 0.1 * weight_derivative[z];
                            //storing the values in a vector
                            vWB.push_back(W[z]);
                    }

                        //calculating the bias
                        bias_derivative = total_diff/9;
                        bias = bias - 0.1 * bias_derivative;
                        vWB.push_back(bias);
                }
            return vWB;

        }

        double CPPLogisticRegression::predict(vector<double> vW){

            static double predictions;
            double X_train_test[14] = {54,1,0,110,239,0,1,126,1,2.8,1,1,3};
            double Wx_test = 0.0;
                //computing σ(W.x)
                for (int j = 0; j < 13; j++){
                    Wx_test += (vW[j] * X_train_test[j]);
                }
                //adding the bias term
                predictions = 1/(1 + exp(-(Wx_test + vW.back())));
                //making the prediction
                if(predictions>=0.5){
                    predictions = 1.0;
                }else{
                    predictions = 0.0;
                }
            return predictions;
        }

extern "C" JNIEXPORT jstring JNICALL
Java_com_terrence_heartndk_MainActivity_testPrediction(
        JNIEnv* env,
        jobject, /* this */
        jstring path) {
            vector<double> vX;
                   const char *name = env->GetStringUTFChars(path, 0);
                    std::string str = name;
                str = str+"/heart.csv";


                CPPLogisticRegression* log_reg = new CPPLogisticRegression();
                vX = log_reg->updateWeightsAndBias(str);
                double sttt = log_reg->predict(vX);
                string yaa = to_string(sttt);
                return env->NewStringUTF(yaa.c_str());
}