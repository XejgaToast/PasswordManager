#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <conio.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

void save();
void read();

int main()
{
    char input;
    while(input != 'e')
    {
        cout << "Generate new password and save (s), read existing password (r) or end program (e)?" << endl;
        cout << "Input: ";
        cin >> input;
        if(input == 's')
        {
            save();
        }
        else if(input == 'r')
        {
            read();
        }
        else if(input == 'e')
        {
            return 0;
        }
        else
        {
            cout << "Illegal input!" << endl;
        }
    }
}

void save()
{
    string name;
    string password = "";
    srand(time(NULL));
    ofstream file;
    file.open("passwords.pm", ofstream::app);
    int pwsize = 0;

    cout << "Number of digits: ";
    cin >> pwsize;
    cout << "Name: ";
    cin >> name;
    file << name << endl;

    for(int i=0; i<pwsize; i++)
    {
        int randNum = rand()%(126-33 + 1) + 33;
        password += randNum;
    }
    cout << "The generated password is: " << password << endl;

    double key = (rand()%92/2)+1;
    cout << "Writing..." << endl;
    file << (key*key)/(key-1) << endl; //Encrypt the key to make it at least a bit harder to decrypt :D


    for(int i=0;i<pwsize;i++)
    {
        password[i]+=key;               //This is the actual encryption. Yes, it is with Caesar :) Highly recommend changing this to another!
    }
    file << password << '§' <<endl;
    return;
}

void read()
{
    string name;
    string line;
    ifstream file;
    string password = "";
    int pwsize = 0;
    file.open("passwords.pm");
    double key;
    bool found = false;

    getline(file,line);
    cout << line << endl;
    while(getline(file,line))
    {
        for(int i=0;i<2 && getline(file,line);i++){}
        cout << line << endl;
    }
    file.clear();
    file.seekg(0);
    cout << "Name: ";
    cin >> name;

    while(getline(file,line))
    {
        if(line == name)
        {
            found = true;
            break;
        }
    }
    if(!found)
    {
        cout << "Password not found!" << endl;
        return;
    }
    getline(file,line);
    key = atof(line.c_str());
    key = round(sqrt(-key+(key*key)/4)+(key/2)); //Here is the decryption of the key: The formula is pretty easy to get, when you have the encryption formula. I highly recommend changing the algorithm!
    getline(file,line);
    for(int i=0; line[i]!='§'; i++)
    {
        password += line[i];
        pwsize++;
    }
    for(int i=0; i<pwsize; i++)
    {
        password[i] -= key;                 //Basically decrypting it
    }
    cout << password << endl << endl << endl;
    return;
}
