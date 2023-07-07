#include <cstring>
#include <string>
#include <vector>
#include <GenshinGachaSimulation\GachaSimulationRec.h>
using namespace std;

/*    
    for(int i = 0;i < totalSimulationAmount;i ++)
    {
        for(;;)
        {
            GachaFallBack fallBackOnce = thisGachaSystem.doGacha(simPlayerData);
            // do Gacha and get fallback
            simPlayerData.updateData(fallBackOnce);
            // refresh player data
            for(int j = 0;j < totalTaticAmount;j ++)
            {
                if(TaticList[j].judgeCondition(simPlayerData)) simPlayerData.updateData(TaticList[j].TaticFallBack());
                //reset player data by the Tatic 
            }
            if(EndSitiuationJudge(simPlayerData)) break;
            // if target was completed
        }
        simRec.AddData(simPlayerData);
        // record and do caculate
    }
    
*/

class Command
{
/* 
 * command set  
 * doSimulation [times]
 * 
 * setTarget [TargetAmount] {[itemName] [amount]}…x"amount" times 
 * 
 * setBanner [5Up1Name] [5Up2Name] [5Arm1Name] [5Arm2Name] 
 * 
 * setTatic [firstBanner] [TaticAmount] {[Tragger] [traggerValue] [Factor] [factorValue] [modifyType] [modifyValue]}…"amount" times
 * 
 */
// Prmt-parameter
public:
    int ID;
    struct setTargetPrmt
    {
        string itemName;
        int amount;
    };

    struct setBannerStu
    {
        string Up1Name,
               Up2Name,
               Arm1Name,
               Arm2Name;
    };

    struct setTatic
    {
        int TraggerID,
            traggerValue,
            FactorID,
            factorValue,
            modifyTypeID,
            modifyValue;
    }

    Command Command(string cmdInput) //对输入字符串进行处理，存入以上指令数据集
    {

    }
}

int main()
{
    //initialization simulation data
    PlayerData simPlayerData = new PlayerData();
    GachaSystem thisGachaSystem = new GachaSystem();
    GachaSimulationRec simRec = new GachaSimulationRec();
    vector<GachaTatic> TaticList;


    //input tatic
    int totalSimulationTimes,totalTaticAmount;

    //begin command recall

    for(;;){  //Main
        string commandString;
        cin >> commandString;   //input command
        Command thiscommand = new Command(commandString);  //initialization class commond and process commond
        switch(thiscommand.GetPrvcommandID()){     //apply commond
            case 0:{
            for(int i = 0;i < totalSimulationTimes;i ++)
            {
                for(;;)
                {
                    GachaFallBack fallBackOnce = thisGachaSystem.doGacha(simPlayerData);
                    // do Gacha and get fallback
                    simPlayerData.updateData(fallBackOnce);
                    if(simPlayerData.EndSitiuationJudge()) break;
                    // refresh player data
                    for(int j = 0;j < totalTaticAmount;j ++)
                    {
                        if(TaticList[j].judgeCondition(simPlayerData)) simPlayerData.updateData(TaticList[j].TaticFallBack());
                        //reset player data by the Tatic 
                    }
                    // if target was completed
                }
                simRec.AddData(simPlayerData);
                // record and do caculate
            }
            };break;
            case 1:{

            };break;
            case 2:{

            };break;
            case 3:{

            };break;
            case 4:{

            };break;
            case 5:{

            };break;
            case 6:{

            };break;
        }
    }

    //count record and produce ans
    // simRec.output();
    return 0;
}