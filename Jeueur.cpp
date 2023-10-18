#include "Jeueur.h"

Jeueur::Jeueur(const std::string &name, int birthday) : name(name), birthday(birthday) {
    cartes.push_back(&Jeu::getInstance().getCarte(94));
    cartes.push_back(&Jeu::getInstance().getCarte(95));
}

int Jeueur::getNum(std::string name){
    int num = 0;
    for(auto it = begin();it != end();it++){
        if((*it).getName() == name)
            num++;
    }
    return num;
}

int Jeueur::getCount() const{
    return count;
}

int Jeueur::getMoney() const {
    return money;
}

int Jeueur::getBirthday() const {
    return birthday;
}

int Jeueur::addMoney(int i){
    money = money + i;
    return money;
}

int Jeueur::redMoney(int i) {
    money = money - i;
    return money;
}

const std::string &Jeueur::getOnce() const {
    return once;
}

const std::string &Jeueur::getName() const {
    return name;
}
void Jeueur::setMoney(int money) {
    Jeueur::money = money;
}

void Jeueur::setName(const std::string &name) {
    Jeueur::name = name;
}

void Jeueur::setBirthday(int birthday) {
    Jeueur::birthday = birthday;
}

void Jeueur::afficherCarte(){
    std::cout<<"          ----------------------------"<<getName()<<"------------------------------\n";
    int n = 0;
    for(auto it = begin();it != end();it++){
        auto im = begin();
        for(im;im != it;im++)
            if((*im).getName() == (*it).getName())
                break;
        if(im == it){
            std::string str;
            str = (*it).getName();
            str.append("*");
            str = str + std::to_string(getNum((*it).getName()));
            std::cout<<std::left<<std::setw(20)<<str;
            n++;
            if(n % 5 == 0 && n != 0)
                std::cout<<"\n";
        }
    }
    std::cout<<"\nmoney: "<<getMoney()<<"\n";
}

bool Jeueur::dice(){
    bool flagEqual= 0;
    if(!turnRailway){//没有翻转火车站
        int _count = (rand() % 6) + 1;
        std::cout<<"the count is: "<<_count<<"\n";
        if(!turnRadio) {//没有翻转广播台
            count = _count;
            return flagEqual;
        }else{//翻转了广播台
            std::cout<<"you want to toss again(y/n)?\n";
            char s;
            std::cin>>s;
            if(s == 'y'){//要求重掷
                int _countAgain = (rand() % 6) + 1;
                std::cout<<"the count is: "<<_countAgain<<"\n";
                count = _countAgain;
                return flagEqual;
            }else{
                count = _count;
                return flagEqual;
            }
        }
    }else{//翻转了火车站
        int n;
        std::cout<<"Choose one dice or tow dices(1/2):"<<std::endl;
        std::cin>>n;
        if(n == 1){//选择1个骰子
            int _count = (rand() % 6) + 1;
            std::cout<<"the count is: "<<_count<<"\n";
            if(!turnRadio) {//没有翻转广播台
                count = _count;
                return flagEqual;
            }
            else{//翻转了广播台
                std::cout<<"you want to toss again(y/n)?\n";
                char s;
                std::cin>>s;
                if(s == 'y') {//要求重掷
                    std::cout << "Choose one dice or tow dices(1/2):" << std::endl;
                    int m;
                    std::cin >> m;
                    if (m == 1) {//选择1个骰子
                        int _countAgain = (rand() % 6) + 1;
                        std::cout << "the count is: " << _countAgain << "\n";
                        count = _countAgain;
                        return flagEqual;
                    } else {//选择2个骰子
                        int _countAgain1 = (rand() % 6) + 1;
                        int _countAgain2 = (rand() % 6) + 1;
                        if (_countAgain1 == _countAgain2)
                            flagEqual = 1;
                        std::cout << "the count is: " << _countAgain1 << " and " << _countAgain2 << "\n";
                        count = _countAgain1 + _countAgain2;
                        return flagEqual;
                    }
                }else{
                    count = _count;
                    return flagEqual;
                }
            }
        }else{//选择2个骰子
            int _count1 = (rand() % 6) + 1;
            int _count2 = (rand() % 6) + 1;
            std::cout<<"the count is: "<<_count1<<" and "<<_count2<<"\n";
            if(!turnRadio){//没有翻转广播台
                if(_count1 == _count2)
                    flagEqual = 1;
                count = _count1 + _count2;
                return flagEqual;
            }else{//翻转了广播台
                std::cout<<"you want to toss again(y/n)?\n";
                char s;
                std::cin>>s;
                if(s == 'y'){//要求重掷
                    std::cout<<"Choose one dice or tow dices(1/2):"<<std::endl;
                    int m;
                    std::cin>>m;
                    if(m == 1) {//选择1个骰子
                        int _countAgain = (rand() % 6) + 1;
                        std::cout << "the count is: " << _countAgain << "\n";
                        count = _countAgain;
                        return flagEqual;
                    }else{//选择2个骰子
                        int _count3 = (rand() % 6) + 1;
                        int _count4 = (rand() % 6) + 1;
                        if(_count3 == _count4)
                            flagEqual = 1;
                        std::cout << "the count is: " << _count3 << " and " << _count4 << "\n";
                        count = _count3 + _count4;
                        return flagEqual;
                    }
                }else{
                    count = _count1 + _count2;
                    return flagEqual;
                }
            }
        }
    }
}

void Jeueur::pay(Jeueur& j) {//给其他玩家钱，传入其他玩家
    if (!flagOther)//如果其他玩家没有红卡，退出pay()
        return;
    if (count == 3) {//如果是3—>咖啡车
        for (auto it = j.begin();it != j.end();it++) {//遍历其他玩家的手牌
            if ((*it).getCount1() == count) {//如果其他玩家有对应点数的红卡
                if(!turnCenter) {//没有建造购物中心
                    if(money >= j.getNum((*it).getName())){//钱数大于卡牌数
                            money -= j.getNum((*it).getName());
                            j.addMoney(j.getNum((*it).getName()));
                    }else{ //钱数小于卡牌数，全给
                        j.addMoney(money);
                        money = 0;
                    }
                }
                else {//建造了购物中心
                    if(money >= 2*j.getNum((*it).getName())){//钱数大于卡牌数*2
                            money -= 2*j.getNum((*it).getName());
                            j.addMoney(2*j.getNum((*it).getName()));
                    }else {//钱数小于卡牌数*2，全给
                        j.addMoney(money);
                        money = 0;
                    }
                }
                break;
            }
        }
    }
    else{//其他（9，10）->餐厅
        for (auto it = j.begin(); it != j.end();it++) {//遍历其他玩家的手牌
            if ((*it).getCount1() == count) {//如果其他玩家有对应点数的红卡
                if(!turnCenter) {//没有建造购物中心
                    if(money >= 2*j.getNum((*it).getName())){//钱数大于卡牌数*2
                        money -= 2*j.getNum((*it).getName());
                        j.addMoney(2*j.getNum((*it).getName()));
                    }else{ //钱数小于卡牌数，全给
                        j.addMoney(money);
                        money = 0;
                    }
                }
                else {//建造了购物中心
                    if(money >= 4*j.getNum((*it).getName())){//钱数大于卡牌数*4
                        money -= 4*j.getNum((*it).getName());
                        j.addMoney(4*j.getNum((*it).getName()));
                    }else {//钱数小于卡牌数*4，全给
                        j.addMoney(money);
                        money = 0;
                    }
                }
                break;
            }
        }
    }
}

void Jeueur::allGet(Jeueur& j){
    if(count == 9){//如果是9->矿场
        for (auto it = j.begin(); it != j.end();it++) {//遍历其他玩家的手牌
            if ((*it).getCount1() == count) //如果其他玩家有对应点数的蓝卡
                j.addMoney(3);
        }
    }else if(count == 10){//10->果园
        for (auto it = j.begin(); it != j.end();it++) {//遍历其他玩家的手牌
            if ((*it).getCount1() == count) //如果其他玩家有对应点数的蓝卡
                    j.addMoney(3);
        }
    }else{//其他(1,2,5)->麦田，农场，林场
        for (auto it = j.begin(); it != j.end();it++) {//遍历其他玩家的手牌
            if ((*it).getCount1() == count && (*it).getCount2() == 0) //如果其他玩家有对应点数的蓝卡(排除蛋糕房)
                j.addMoney(1);//加1
        }
    }
}

void Jeueur::selfGet(){
    if (count == 1){
        for(auto it = begin(); it !=end();it++) {//遍历本玩家的手牌
            if ((*it).getName() == "cornfield")//如果有麦田
                money += 1;//加1
        }
    }else if(count == 2){//2->农场
        for(auto it = begin(); it != end();it++){//遍历本玩家的手牌
            if((*it).getName() == "farm")//如果有农场
                    money += 1;//加1
            if((*it).getName() == "bakery"){//如果有蛋糕房
                if(!turnCenter)//如果没有建成购物中心
                    money += 1;//加1
                else//如果建成了购物中心
                    money += 2;//加2
            }
        }
    }else if(count == 3){
        for(auto it = begin(); it != end();it++){//遍历本玩家的手牌
            if((*it).getName() == "bakery"){//如果有蛋糕房
                if(!turnCenter)//如果没有建成购物中心
                    money += 1;//加1
                else//如果建成了购物中心
                    money += 2;//加2
            }
        }
    }else if(count == 4){
        for(auto it = begin(); it != end();it++) {//遍历本玩家的手牌
            if ((*it).getName() == "store") {//如果有便利店
                if (!turnCenter)//如果没有建成购物中心
                    money += 3;//加3
                else//如果建成了购物中心
                    money += 6;//加6*牌数
            }
        }
    }else if(count == 5){
        for(auto it = begin(); it != end();it++) {//遍历本玩家的手牌
            if ((*it).getName() == "forest")//如果有林场
                money += 1;//加1
        }
    }else if(count == 7){
        for(auto it = begin(); it != end();it++) {//遍历本玩家的手牌
            if ((*it).getName() == "cheeseFactory") {//如果有奶酪工厂
                int n = 0;//用于存储农场卡牌数
                for(auto im = begin(); im != end();it++){
                    if((*im).getName() == "farm")
                        n += 1;
                }
                money += 3*n;//加3*农场卡牌数
            }
        }
    }else if(count == 8){
        for(auto it = begin(); it != end();it++) {//遍历本玩家的手牌
            if ((*it).getName() == "furnitureFactory") {//如果有家具工厂
                int n = 0,m = 0;//用于存储林场，矿场卡牌数
                for(auto im = begin(); im != end();it++){
                    if((*im).getName() == "forest")
                        n += 1;
                    if((*im).getName() == "mineField")
                        m += 1;
                }
                money += 3*(n+m);//加3*(林场+矿场卡牌数)
            }
        }
    }else if(count == 9){
        for(auto it = begin(); it != end();it++){//遍历本玩家的手牌
            if((*it).getName() == "mineField")//如果有矿场
                money += 5;//加5
        }
    }
    else if(count == 10){
        for(auto it = begin(); it != end();it++){//遍历本玩家的手牌
            if((*it).getName() == "orchard")//如果有果园
                money += 3;//加3
        }
    }else{
        for(auto it = begin(); it != end();it++) {//遍历本玩家的手牌
            if ((*it).getName() == "market") {//如果有果蔬超市
                int n = 0,m = 0;//用于存储麦田，果园卡牌数
                for(auto im = begin(); im != end();it++){
                    if((*im).getName() == "cornfield")
                        n += 1;
                    if((*im).getName() == "market")
                        m += 1;
                }
                money += 3*(n+m);//加3*(麦田+果园卡牌数)
            }
        }
    }
}

void Jeueur::changeCarte(Jeueur& j,Carte jCname,Carte sCname) {
    for (auto it = j.begin(); it != j.end(); it++) {
        if ((*it).getName() == jCname.getName()) {//被选中的玩家减牌
            j.cartes.erase(it);
            break;
        }
        j.cartes.push_back(&sCname);
        for (auto it = begin(); it !=end(); it++) {
            if ((*it).getName() == sCname.getName()) {//玩家减牌
                cartes.erase(it);
                break;
            }
        }
        cartes.push_back(&jCname);
    }
}

void Jeueur::getJeueur5(Jeueur& j){
    if(j.getMoney() >= 5){
        money += 5;
        j.redMoney(5);
    }else{
        money += j.getMoney();
        j.setMoney(0);
    }
}

void Jeueur::getJeueur2(Jeueur& j){
    if(j.getMoney() >= 2){
        money += 2;
        j.redMoney(2);
    }else{
        money += j.getMoney();
        j.setMoney(0);
    }
}

bool Jeueur::isFlagOnce() const {
    return flagOnce;
}

bool Jeueur::isTurnRailway() const {
    return turnRailway;
}

bool Jeueur::isTurnCenter() const {
    return turnCenter;
}

bool Jeueur::isTurnPark() const {
    return turnPark;
}

bool Jeueur::isTurnRadio() const {
    return turnRadio;
}

Carte& Jeueur::getCarte(std::string name){
    for(auto it = begin(); it != end();it++){
        if((*it).getName() == name)
            return (*it);
    }
}

void Jeueur::achete(std::string name,BankCarte& bank){
    if(name == "railwayStation"){
        turnRailway = 1;
        money -= 4;
        cartes.push_back(&Jeu::getInstance().getCarte(90));
    }else if(name == "shoppingCenter") {
        turnCenter = 1;
        money -= 10;
        cartes.push_back(&Jeu::getInstance().getCarte(91));
    }else if(name == "amusementPark") {
        turnPark = 1;
        money -= 16;
        cartes.push_back(&Jeu::getInstance().getCarte(92));
    }else if(name == "radioStation") {
        turnRadio = 1;
        money -= 22;
        cartes.push_back(&Jeu::getInstance().getCarte(93));
    }else if(name == "businessCenter"|| name == "gym" || name == "bandstand") {
//        if(flagOnce)
//            std::cout<<"error";
        flagOnce = 1;
        cartes.push_back(bank.getCarte(name));

        money = money - bank.getPrice(name);
        bank.redCarte(name);
    }else{
        cartes.push_back(bank.getCarte(name));
        money = money - bank.getPrice(name);
        bank.redCarte(name);
    }
}

const std::vector<Carte *> &Jeueur::getCartes() const {
    return cartes;
}
