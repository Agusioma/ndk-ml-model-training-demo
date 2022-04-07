#include <jni.h>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

	vector<vector<string>> content;
	vector<string> row;
	string line, word;
	int noOfRows;
	int noOfColumns;


string checkFirst(string fname){
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
	noOfRows = content.size();
	noOfColumns = content[0].size();
	int dataset[][];
	int datasetSize = content.size();
	//minusing 1 because of the header row values(age, sex etc)
	int indices[datasetSize-1];

	for (int i = 0; i < datasetSize-1; i++) {
      indices[i] =  i + 1;
    }

	int* shuffled_indices = shuffle_indices(indices, datasetSize-1);

	for (int i = 0; i < datasetSize-1; i++) {

      indices[i] =  i + 1;
    }

	return to_string(content[0].size());
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
    return arr;
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
    //str = str+"/heart.csv";
    //string tt = checkFirst(str);
    int array[2][2] = {
    {0,2},
    {1,4}
    };
    passFunc(array);
    string g = to_string(passFunc(array));
    return env->NewStringUTF(g.c_str());
}