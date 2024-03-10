#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include "class.h"
#include <fstream>
#define SIZE 256

using namespace std;

int main(int argc, char *argv[])
{
    fstream file;
    string str;
    file.open("words.txt",ios::in);
	Trie *n = new Trie();
    if(!file.is_open())
        return -1;
    while (file >> str)
    {
        n->InsertNode(str);
    }
	string word,word2,w1,choice1;
	char ch1;
	START:
        cout<<"SMART KEYBOARD\n"<<endl;
    start:
    cout << "Please enter word" << endl;
    cin >> word;

    vector<string> res;

    n->CorrectSpell(word, res);

    vector<string>::iterator itr;
    if (res.size() > 0)
    {
    start1:
        for(itr = res.begin(); itr != res.end(); ++ itr)
        {
            cout << *itr << endl;
        }
        START1:
        cout<<"is your word among these?\n";
        cin>>choice1;
        if(choice1=="n"||choice1=="N")
        {
            cout << "Your word is not in dictionary\n"<<"do you want to add your word to the dictionary[y/n]?\n"<<endl;
            cin>>ch1;
            if(ch1=='y'||ch1=='Y')
            {
                cout<<"enter word\n";
                cin>>w1;
                n->InsertNode(w1);
                goto start2;
            }
            else
            {
                if(ch1=='n'||ch1=='N')
                {
                start2:
                    cout<<"press 1 to continue\n"<<"press 0 to exit\n"<<endl;
                    cin>>ch1;
                    if(ch1=='1')
                    {
                        goto start;
                    }
                    else
                    {
                        if(ch1=='0')
                        {
                            system("cls");
                            exit(0);
                        }
                        else
                        {
                            cout<<"invalid\n";
                            goto start1;
                        }
                    }
                }
                else
                {
                    cerr<<"invalid\n";
                    goto START1;
                }
            }
        }
        else
        {
            if(choice1=="y"||choice1=="Y")
            {
                cout<<"enter word\n";
                cin>>word2;
                cout<<word2<<" is in the dictionary\n";
                goto start2;
            }
            else
            {
                cerr<<"invalid:\n";
                goto START1;
            }
        }
    }
    else
    {
        cout << word<<" is in the dictionary\n" << endl;
    }
    goto start2;
}

