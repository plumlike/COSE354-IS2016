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
    char encrypted[50]="QFXWJEILAWFKMUMZALGAKMPUQLAVY"; //��ȣȭ�� ���ڿ�
         encrypted_size = strlen(encrypted);

    //���ͳ� �ڷḦ �����Ͽ� �������� ���� ���� �����ϴ� ���ĺ� ������ �̸� �迭�� �����س��´�.
    char frequncy_order[30] = {'E','T','A','O','I','N','S','H','R','D','L','C','U','M','W','F','G','Y','P','B','V','K','J','Q','X','Z'};

    cout <<endl<<" ��ȣ�� : QFXWJEILAWFKMUMZALGAKMPUQLAVY " << endl
        <<" Hint 1: Key consists of only English letters and its size is 3"<<endl
        <<" Hint 2: The plaintext starts with 'I'"<<endl
        <<" ���� ������ �������� �ص��� �����մϴ�..." <<endl<<endl;

    //1. ������ �־��� ������ Ȱ���Ͽ� �ص�Ű�� ù��° ���ڸ� ���Ѵ�.
    decrypted[0][0]='I';
    key[0][0] = encrypted[0]- decrypted[0][0];
    if(key[0][0]  < 0)
        key[0][0]  +=26;
    key[0][0]  = key[0][0] %26;
    key[0][0] +='A';

    for(int i=1 ; i <50 ; i++)
        key[i][0] = key[0][0]; //�����Ѹ�� Ű���� �迭�� ��ݱ��� ù��° Ű���� ����ִ´�.
    //..end 1.

   // 2-1. �Ű�� ��ȣȭ�Ǵ����� ���� �׷����� ������.
    char group2[12]={0,}; // Ű�� �ι�° ���ڷ� ��ȣȭ �� ���ڱ׷�
    char group3[12]={0,}; // Ű�� ������ ���ڷ� ��ȣȭ �� ���ڱ׷�

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

    //2-2. �� �׷쿡�� ��� ���ڰ� ���Ǿ����� ���Ѵ�.(�� �׷��� �� ���� ���� - �ߺ��Ǵ� ���ڼ� )
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

    //3. �������� �����ϴ� ���ĺ��󵵸� ����Ͽ� ������ Ű�� ������ ������.
    int k=0;
    for(int i=0; i< group2_letter_num; i++ ){
        for(int j=0; j < group2_letter_num; j++,k++){
            key[k][1] = frequncy_order[i];
            key[k][2] = frequncy_order[j];
        }
    }

    //4. ������ Ű�� ������ �̿��Ͽ� ��ȣȭ�� �����Ѵ�.
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

   //��ȣȭ�� ������.
}
