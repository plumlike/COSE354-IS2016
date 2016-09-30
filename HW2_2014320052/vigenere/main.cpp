#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
using namespace std;

int main()
{

    int i=0,j=0,key_size=3,encrypted_size=0;
    int group2_size=0, group2_duplicated=0, group2_letter_num=0,
        group3_size=0, group3_duplicated=0, group3_letter_num=0;

    char key[50][3]={0,};
    char decrypted[50][30] ={0,};
    char encrypted[50]="QFXWJEILAWFKMUMZALGAKMPUQLAVY"; //암호화된 문자열
         encrypted_size = strlen(encrypted);

    //인터넷 자료를 참고하여 영문에서 가장 많이 등장하는 알파벳 순으로 미리 배열에 저장해놓는다.
    char frequncy_order[30] = {'E','T','A','O','I','N','S','H','R','D','L','C','U','M','W','F','G','Y','P','B','V','K','J','Q','X','Z'};

    cout <<endl<<" 암호문 : QFXWJEILAWFKMUMZALGAKMPUQLAVY " << endl
        <<" Hint 1: Key consists of only English letters and its size is 3"<<endl
        <<" Hint 2: The plaintext starts with 'I'"<<endl
        <<" 위의 조건을 바탕으로 해독을 시작합니다..." <<endl<<endl;

    //1. 과제로 주어진 조건을 활용하여 해독키의 첫번째 글자를 구한다.
    decrypted[0][0]='I';
    key[0][0] = encrypted[0]- decrypted[0][0];
    if(key[0][0]  < 0)
        key[0][0]  +=26;
    key[0][0]  = key[0][0] %26;
    key[0][0] +='A';

    for(int i=1 ; i <50 ; i++)
        key[i][0] = key[0][0]; //가능한모든 키값의 배열에 방금구한 첫번째 키값을 집어넣는다.
    //..end 1.

   // 2-1. 어떤키로 복호화되는지에 따라 그룹으로 나눈다.
    char group2[12]={0,}; // 키의 두번째 글자로 복호화 될 글자그룹
    char group3[12]={0,}; // 키의 세번쨰 글자로 복호화 될 글자그룹

    for(i=0,j=0; i <= encrypted_size/key_size ;i++,j++){
        group2[i] = encrypted[1 + key_size*j];
        if(group2[i])
            group2_size++;
    }

    for(i=0,j=0; i <= encrypted_size/key_size ;i++,j++){
        group3[i] = encrypted[2 + key_size*j];
        if(group3[i])
            group3_size++;
    } //..end 2-1.

    //2-2. 각 그룹에서 몇개의 글자가 사용되었는지 구한다.(각 그룹의 총 글자 갯수 - 중복되는 글자수 )
    for(int i=0; i<group2_size; i++)
        for(int j=i+1; j<group2_size; j++)
            if(group2[i]==group2[j])
             group2_duplicated++;

    group2_letter_num = group2_size-group2_duplicated;

    for(int i=0; i<group3_size; i++)
        for(int j=i+1; j<group3_size; j++)
            if(group3[i]==group3[j])
             group3_duplicated++;

    group3_letter_num = group3_size-group3_duplicated; //..end..2-2

    //3. 영문에서 등장하는 알파벳빈도를 고려하여 가능한 키의 조합을 만들어낸다.
    int k=0;
    for(int i=0; i< group2_letter_num; i++ ){
        for(int j=0; j < group2_letter_num; j++,k++){
            key[k][1] = frequncy_order[i];
            key[k][2] = frequncy_order[j];
        }
    }

    //4. 가능한 키의 조합을 이용하여 복호화를 실행한다.
   for(k=0; k < group2_letter_num*group2_letter_num; k++ ){
        char encrypt[50]="QFXWJEILAWFKMUMZALGAKMPUQLAVY";
        for(i=0,j=0; i<encrypted_size;i++)
        {
            j=i % key_size;
                if((encrypt[i] >='A')&&(encrypt[i]<='Z'))
                {
                    encrypt[i]-='A'; //cout <<"here :" << key[k][j]<<endl;
                    key[k][j]-='A';
                    if((encrypt[i]-key[k][j])<0)
                        encrypt[i]+=26;

                    decrypted[k][i]=(encrypt[i]-key[k][j])%26;
                    decrypted[k][i]+='A';
                    key[k][j]+='A';
                }
        }
         cout << "If key:"<<key[k][0]<<key[k][1]<<key[k][2]<<" -> "<<decrypted[k] <<endl;
   }

   //복호화가 끝났다.
}
