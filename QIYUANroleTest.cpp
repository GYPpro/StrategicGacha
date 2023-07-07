#include <iostream>
#include <windows.h>
#include <myMathTool.h>
#include <myDisplyTool.h>

using namespace std;

double GET_P(int index)//用于获取目前概率
{
    if (index < 64) return 0.006;
    if (index < 80) return ((index-63)*0.06 + 0.006);
    return 1;
}

int QR_rand(double p)//核心抽卡算法
{
    int r;
    //r = (int)(rand()*1000)/RAND_MAX;

    int tmp;//概率分配中间变量
    tmp = (int)(1000*p) / 2;
    r = rand();
    for(;r >= 30000;)r = rand();
    r %= 1000; //0-999 

    if (r < tmp) return 1;    //出货
    if (r < 2 * tmp) return 2; //歪了
    return 0;                  //没出
    
}

int main()
{
    int PER_TEST[200],  //记录每次祈愿模拟的数据
        TEST_REC[200],  //记录模拟统计UP角色数据
        SUM_REC = 0,    //记录UP角色数量数据
        TEST_T_REC[200],//记录模拟统计所有角色数据
        SUM_T_REC = 0,  //记录所有角色数据
        TOTL_TIMES = 0, //记录模拟次数
        RAND_TMP = 0;   //随机数生成中间量
    int FEI;            //命定值
    double P;           //实时概率
    srand(114514);

    //输出实时概率
    cout << "第n抽    概率（%。）" << endl;
    for (int i = 1;i <= 80;i ++)
    {
        cout << i << "  " << (int)(1000*GET_P(i))<< endl;
    }

    //数据初始化
    for (int i = 0;i < 240;i ++)
    {
        PER_TEST[i] = 0;
        TEST_REC[i] = 0;
        TEST_T_REC[i] = 0;
    }

    //正式模拟
    cout << "输入模拟次数(大于0小于2^31)" << endl;
    cin >> TOTL_TIMES;

    system("cls");
    cout << "CACULATING……" << endl;
    
    for (int i = 0;i < TOTL_TIMES;i ++)
    {
        if(TOTL_TIMES>=1650) if(!(i % (TOTL_TIMES/1650))) UpdatePrc(TOTL_TIMES,i,40);
        FEI = false;//重置小保底
        for (int j = 1 , r = 1; j <= 180;j ++)//进行一轮抽卡模拟
        {
            //r负责计算概率，以保证小保底重置概率提升
            P = GET_P(r);//计算实时概率
            int RES = 0;//出货判定中间量
            RES = QR_rand(P);//获取出货判定
            if (RES == 1) {//出货
                SUM_REC ++;
                SUM_T_REC ++;
                TEST_REC[j] ++;
                TEST_T_REC[r] ++;
                break;
            }
            if ((RES == 2) && (FEI == true)) {//大保底机制
                SUM_REC ++;
                SUM_T_REC ++;
                TEST_REC[j] ++;
                TEST_T_REC[r] ++;
                break;
            }
            if (RES == 2) {//歪了！
                SUM_T_REC ++;
                TEST_T_REC[r] ++;
                FEI = true;//进入大保底
                r = 1;
                continue;
            }
            r ++;
        }
    }

    double T_EXPT = 0,//出金期望
           EXPT = 0;  //UP角色期望
    unsigned long long CACU_TMP = 0;//格式转化与计算中间量

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
 
    cout << "UP期望:" << EXPT << endl;
    cout << "出金期望:" << T_EXPT << endl;
    cout << "UP角色占总出金的 "  <<  (double)SUM_REC  / (double)SUM_T_REC * 100 << " %" << endl;
    cout << "---------------------" << endl;

    int dif_Step = 0;//梯度图每个方块代表的数值
    dif_Step =(int)( FindMax(&TEST_REC[0],180) / 32);
    
    
 
    cout << "出金梯度图" << endl;
    cout << "每一个方块代表" << dif_Step << endl;
    
    for (int i = 0;i < 90;i ++)
    {
        cout << i << " - ";
        int Wed = 0;
        int Tmp_R = TEST_REC[i];
        for (;((Tmp_R / dif_Step)) && (Tmp_R > 0);Wed ++)
        {
            cout << "■";
            Tmp_R -= dif_Step;
        }
        for (;Wed < 40;Wed++) cout << " ";
        cout << TEST_REC[i];
        cout << endl;
    }

    system("pause");
    return 0;
}