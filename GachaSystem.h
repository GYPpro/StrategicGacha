//#include <string>
#include <iostream>
#include <vector>
#include <hash_map>
#include <stdlib.h>
#include <ctime>
using namespace std;

class Item{
public:
    Item()
    {
        ID = 0;
        name = '';
        rarity = 0;
        itemType = 0;
        ifPity = 0;
    }

    Item(string nameInput,int IDInput,int rarityTnput,int itemTypeInput,int ifPityInput)
    {
        ID = IDInput;
        name = nameInput;
        rarity = rarityTnput;
        itemType = itemTypeInput;
        ifPity = ifPityInput;
    }
    
    operator!=(Item b)
    {
        return (ID == b.ID);
    }

public:
    int ID;         //Produced UUID
    string name;    //Name
    int rarity;     //rarity              4/5
    int itemType;   //Characters or Arms  1-Characters 2-Arms
    int ifPity;     //ifUP                1-UP   2-Permanent
};

class ItemList{
private:
    vector<vector<Item>> ItemListData;

public:
/*
 * Item List 
 * ID marker
 * 4 rarity Character Up :1
 * 4 rarity Arm Up :2
 * 5 rarity Character Up :3
 * 5 rarity Arm Up :4
 * 4 rarity Character Permanent :5
 * 4 rarity arm Permanent :6
 * 5 rarity Character Permanent :7
 * 5 rarity Arm Permanent :7
 */

    Item itemFilter(int ID)
    {
        int Classify = ID/100;
        switch (Classify)
        {
        case 411:
            return ItemListData[1][ID%100];
            break;
        case 421:
            return ItemListData[2][ID%100];
            break;
        case 511:
            return ItemListData[3][ID%100];
            break;
        case 521:
            return ItemListData[4][ID%100];
            break;
        case 412:
            return ItemListData[6][ID%100];
            break;
        case 422:
            return ItemListData[7][ID%100];
            break;
        case 512:
            return ItemListData[8][ID%100];
            break;
        case 522:
            return ItemListData[9][ID%100];
            break;
        
        default: return Item();
            break;
        }
    }

    Item itemFilter(string name)
    {
        for (int i = 0; i < ItemListData.size(); i++)
        {
            for(int j = 0;j < ItemListData[i].size(); j ++)
            {
                if(ItemListData[i][j].name == name) return ItemListData[i][j];
            }
        }
    }

    vector<Item> itemFilter(int rarity,int itemType,int Permanents)
    {

        int Classify = 100*rarity + 10*itemType + Permanents;
        switch (Classify)
        {
        case 411:
            return ItemListData[1];
            break;
        case 421:
            return ItemListData[2];
            break;
        case 511:
            return ItemListData[3];
            break;
        case 521:
            return ItemListData[4];
            break;
        case 412:
            return ItemListData[6];
            break;
        case 422:
            return ItemListData[7];
            break;
        case 512:
            return ItemListData[8];
            break;
        case 522:
            return ItemListData[9];
            break;
        
        default: return ;
            break;
        }
    }

    void AddItem(string name,int rarity,int itemType,int Permanents)
    {
        int Classify = 100*rarity + 10*itemType + Permanents;
        switch (Classify)
        {
        case 411:
            return ItemListData[1].push_back(Item(name,Classify*100+ItemListData[1].size(),rarity,itemType,Permanents));
            break;
        case 421:
            return ItemListData[2].push_back(Item(name,Classify*100+ItemListData[1].size(),rarity,itemType,Permanents));
            break;
        case 511:
            return ItemListData[3].push_back(Item(name,Classify*100+ItemListData[1].size(),rarity,itemType,Permanents));
            break;
        case 521:
            return ItemListData[4].push_back(Item(name,Classify*100+ItemListData[1].size(),rarity,itemType,Permanents));
            break;
        case 412:
            return ItemListData[6].push_back(Item(name,Classify*100+ItemListData[1].size(),rarity,itemType,Permanents));
            break;
        case 422:
            return ItemListData[7].push_back(Item(name,Classify*100+ItemListData[1].size(),rarity,itemType,Permanents));
            break;
        case 512:
            return ItemListData[8].push_back(Item(name,Classify*100+ItemListData[1].size(),rarity,itemType,Permanents));
            break;
        case 522:
            return ItemListData[9].push_back(Item(name,Classify*100+ItemListData[1].size(),rarity,itemType,Permanents));
            break;
        
        default: return ;
            break;
        }
    }

    bool operator==(ItemList b)
    {
        if(ItemListData.size() == b.ItemListData.size())
        {
            for(int i = 0;i < ItemListData.size();i ++)
            {
                if(ItemListData[i].size() == b.ItemListData[i].size())
                {
                    for(int j = 0;j < ItemListData[i].size)
                    {
                        if(ItemListData[i][j] != b.ItemListData[i][j]) return false;
                    }
                } else return false;
            }
        } else return false; 
        return true;
    }

    void overWrite(ItemList NewData)
    {
        ItemListData = NewData.ItemListData;
    }

};

class PlayerData{
public:
    int WaterLevel5 = 0;   //目前水位5
    int WaterLevel4 = 0;   //目前水位4
    int paneleValue = 0;   //命定值
    int bannerValue = 0;   //当前卡池  11 12 21 22
 
    ItemList Package,
             Target;
    
public:
    PlayerData(ItemList TargetInput)
    {

    }

    void UpdateData(GachaFallBack FallBack)//根据记录刷新玩家信息
    {

    }
    
    void UpdateData(PlayerData newData)     //手动刷新玩家信息
    {

    }

    bool EndSitiuationJudge()
    {
        return Package.compare(Target);
    }

};

class GachaBannerData{
public:
    ItemList BannerItem;
    int ID;   //1n 2n:
    //Arm :up1 2/5 up2 2/5 other 1/5

public:
    GachaBannerData(ItemList initialization,int IDit)
    {
        BannerItem.overWrite(initialization);
        ID=IDit;
    }   


    int getCharacter5Percent(int waterLevel)
    {
        double P;
        if (waterLevel < 74) P = 0.006;
        else if (waterLevel < 90) P = ((waterLevel-73)*0.06 + 0.006);
        else P=1
        return (int)(1000*P);
    }

    int getArm5Percent(int waterLevel)
    {
        double P;
        if (waterLevel < 64) P = 0.006;
        else if (waterLevel < 80) P = ((waterLevel-63)*0.06 + 0.006);
        else P = 1;
        return (int)(1000*P);
    }

    int getCharacter4Percent(int waterLevel)
    {
        double P;
        if (waterLevel < 64) P = 0.006;
        else if (waterLevel < 80) P = ((waterLevel-63)*0.06 + 0.006);
        else P = 1; 
        return (int)(1000*P);
    }

    int getArm4Percent(int waterLevel)
    {
        double P;
        if (waterLevel < 64) P = 0.006;
        else if (waterLevel < 80) P = ((waterLevel-63)*0.06 + 0.006);
        else P = 1;
        return (int)(1000*P);
    }

    int get5Percent(int waterLevel) 
    {
        switch (ID/10)
        {
        case 1:{
            double P;
            if (waterLevel < 74) P = 0.006;
            else if (waterLevel < 90) P = ((waterLevel-73)*0.06 + 0.006);
            else P=1
            return (int)(1000*P);
        }
            break;
        case 2:{
            double P;
            if (waterLevel < 64) P = 0.006;
            else if (waterLevel < 80) P = ((waterLevel-63)*0.06 + 0.006);
            else P = 1;
            return (int)(1000*P);
        }
            break;
        
        default:
            return -1
            break;
        }
    }

    int get4Percent(int waterLevel)//▲概率调整未完成//
    {
        switch (ID/10)
        {
        case 1:{
            double P;
            if (waterLevel < 74) P = 0.006;
            else if (waterLevel < 90) P = ((waterLevel-73)*0.06 + 0.006);
            else P=1
            return (int)(1000*P);
        }
            break;
        case 2:{
            double P;
            if (waterLevel < 64) P = 0.006;
            else if (waterLevel < 80) P = ((waterLevel-63)*0.06 + 0.006);
            else P = 1;
            return (int)(1000*P);
        }
            break;
        
        default:
            return -1
            break;
        }
    }

    int getPaneleNeed()
    {
        return ID%10;
    }

    void UpdateBanner(ItemList NewItemList)
    {
        BannerItem.overWrite(NewItemList);
    }
        
};

class GachaFallBack{
public:
    GachaFallBack(PlayerData thisPlayerData,GachaBannerData thisBannerData,Item thisFallBack)
    {
        prvPlayerData = thisPlayerData;
        BannerData = thisBannerData;
        FallBackItem = thisFallBack;
    }

    PlayerData prvPlayerData;
    GachaBannerData BannerData;
    Item FallBackItem;
};

class GachaSystem{
private: 
    int FullRand(int randMax)
    {
        srand(time(114514));
        int rTmp = rand();
        int MaxModValue = 32767 - 32767 % randMax;
        for(;rTmp >= MaxModValue;) r = rand();
        return rTmp % randMax;
    }

    Item ListRand(vector<Item> sorce)
    {
        int randAns = FullRand(sorce.size());
        return sorce[randAns];
    }

    int PersentRand(int P,int MAXp)
    {
        if(p < FullRand(MAXp)) return true;
        else return false;
    }
 
public:
    // GachaSystem(GachaBannerData InitializationData)//初始化抽卡系统
    // {
    //     bannerData = InitializationData;
    // }

    GachaFallBack doGacha(PlayerData thisPlayerData,GachaBannerData BannerData)//抽卡核心
    {
        if(PersentRand(BannerData.get5Percent(thisPlayerData.WaterLevel5),1000))
        {
            if(thisPlayerData.paneleValue >= BannerData.getPaneleNeed())
                return GachaFallBack(thisPlayerData,BannerData,BannerData.BannerItem.itemFilter(51100+BannerData.ID%10));
            else if(PersentRand(1,2))
                return GachaFallBack(thisPlayerData,BannerData,BannerData.BannerItem.itemFilter(51100+BannerData.ID%10));
            else return ;
        }else if(PersentRand(BannerData.get4Percent(thisPlayerData.WaterLevel4),1000))
        {

        }
    }

};
