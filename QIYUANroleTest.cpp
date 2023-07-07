#include <iostream>
#include <windows.h>
#include <myMathTool.h>
#include <myDisplyTool.h>

using namespace std;

double GET_P(int index)//���ڻ�ȡĿǰ����
{
    if (index < 64) return 0.006;
    if (index < 80) return ((index-63)*0.06 + 0.006);
    return 1;
}

int QR_rand(double p)//���ĳ鿨�㷨
{
    int r;
    //r = (int)(rand()*1000)/RAND_MAX;

    int tmp;//���ʷ����м����
    tmp = (int)(1000*p) / 2;
    r = rand();
    for(;r >= 30000;)r = rand();
    r %= 1000; //0-999 

    if (r < tmp) return 1;    //����
    if (r < 2 * tmp) return 2; //����
    return 0;                  //û��
    
}

int main()
{
    int PER_TEST[200],  //��¼ÿ����Ըģ�������
        TEST_REC[200],  //��¼ģ��ͳ��UP��ɫ����
        SUM_REC = 0,    //��¼UP��ɫ��������
        TEST_T_REC[200],//��¼ģ��ͳ�����н�ɫ����
        SUM_T_REC = 0,  //��¼���н�ɫ����
        TOTL_TIMES = 0, //��¼ģ�����
        RAND_TMP = 0;   //����������м���
    int FEI;            //����ֵ
    double P;           //ʵʱ����
    srand(114514);

    //���ʵʱ����
    cout << "��n��    ���ʣ�%����" << endl;
    for (int i = 1;i <= 80;i ++)
    {
        cout << i << "  " << (int)(1000*GET_P(i))<< endl;
    }

    //���ݳ�ʼ��
    for (int i = 0;i < 240;i ++)
    {
        PER_TEST[i] = 0;
        TEST_REC[i] = 0;
        TEST_T_REC[i] = 0;
    }

    //��ʽģ��
    cout << "����ģ�����(����0С��2^31)" << endl;
    cin >> TOTL_TIMES;

    system("cls");
    cout << "CACULATING����" << endl;
    
    for (int i = 0;i < TOTL_TIMES;i ++)
    {
        if(TOTL_TIMES>=1650) if(!(i % (TOTL_TIMES/1650))) UpdatePrc(TOTL_TIMES,i,40);
        FEI = false;//����С����
        for (int j = 1 , r = 1; j <= 180;j ++)//����һ�ֳ鿨ģ��
        {
            //r���������ʣ��Ա�֤С�������ø�������
            P = GET_P(r);//����ʵʱ����
            int RES = 0;//�����ж��м���
            RES = QR_rand(P);//��ȡ�����ж�
            if (RES == 1) {//����
                SUM_REC ++;
                SUM_T_REC ++;
                TEST_REC[j] ++;
                TEST_T_REC[r] ++;
                break;
            }
            if ((RES == 2) && (FEI == true)) {//�󱣵׻���
                SUM_REC ++;
                SUM_T_REC ++;
                TEST_REC[j] ++;
                TEST_T_REC[r] ++;
                break;
            }
            if (RES == 2) {//���ˣ�
                SUM_T_REC ++;
                TEST_T_REC[r] ++;
                FEI = true;//����󱣵�
                r = 1;
                continue;
            }
            r ++;
        }
    }

    double T_EXPT = 0,//��������
           EXPT = 0;  //UP��ɫ����
    unsigned long long CACU_TMP = 0;//��ʽת��������м���

    for (int i = 0;i < 180;i ++)
    {
        CACU_TMP += TEST_REC[i] * i;
    }

    EXPT = (double)CACU_TMP / (double)SUM_REC;

    CACU_TMP = 0;

    for (int i = 0;i < 180;i ++)
    {
        CACU_TMP += TEST_T_REC[i] * i;
    }

    T_EXPT = (double)CACU_TMP / (double)SUM_T_REC;

    system("cls");
 
    cout << "UP����:" << EXPT << endl;
    cout << "��������:" << T_EXPT << endl;
    cout << "UP��ɫռ�ܳ���� "  <<  (double)SUM_REC  / (double)SUM_T_REC * 100 << " %" << endl;
    cout << "---------------------" << endl;

    int dif_Step = 0;//�ݶ�ͼÿ������������ֵ
    dif_Step =(int)( FindMax(&TEST_REC[0],180) / 32);
    
    
 
    cout << "�����ݶ�ͼ" << endl;
    cout << "ÿһ���������" << dif_Step << endl;
    
    for (int i = 0;i < 90;i ++)
    {
        cout << i << " - ";
        int Wed = 0;
        int Tmp_R = TEST_REC[i];
        for (;((Tmp_R / dif_Step)) && (Tmp_R > 0);Wed ++)
        {
            cout << "��";
            Tmp_R -= dif_Step;
        }
        for (;Wed < 40;Wed++) cout << " ";
        cout << TEST_REC[i];
        cout << endl;
    }

    system("pause");
    return 0;
}