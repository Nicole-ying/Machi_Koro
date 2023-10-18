#include "Controleur.h"

Jeueur& Controleur::getJeueur(std::string name) {
    for(int i = 0; i < JeueurNum ; i++){
        if(J[i]->getName() == name)
            return *J[i];
    }
}

int Controleur::choseFirst(){//得到第一个玩家的下标
    int i=0;
    int max = J[0]->getBirthday();
    for(int k = 1; k < JeueurNum;k++){
        i = max >= J[k]->getBirthday()? i:i+1;
        max = max >= J[k]->getBirthday()? max:J[k]->getBirthday();
    }
    return i;
}

void Controleur::rearrange(){//重新分配向量空间，让被选为第一的人作为向量空间的第一位
    int i = choseFirst();
    std::cout<<"The first player is "<<J[i]->getName()<<std::endl;
    for(int k = 0 ; k < i ; k++){
        J.push_back(J[0]);
        J.erase(J.begin());
    }
}

void Controleur::afficherAll(){
    for(int i = 0; i < JeueurNum ;i++)
        J[i]->afficherCarte();
}

bool Controleur::win(Jeueur j){
    return (j.isTurnRailway() && j.isTurnCenter() && j.isTurnPark() && j.isTurnRadio());//短路与，判断是否都建成
}

void Controleur::process(){
    bool flag = 0;
    for(int i = 0;i < JeueurNum|| !flag ;i++){//经过所有玩家回合
        bank.afficher();
        std::cout<<"Turn of "<<J[i]->getName()<<std::endl;
        bool equal = J[i]->dice();//掷骰子,并得到两个骰子是否相同
        if(J[i]->getCount() == 3||J[i]->getCount() == 9||J[i]->getCount() == 10){ //进行红卡的判定
            int n = i;//n得到当前玩家的下标
            for(int k = 0;k < JeueurNum - 1;k++){//循环玩家数减1次
                if(!J[i]->getMoney())
                break;//当前玩家没有钱了，退出循环
                if(n - 1 >= 0){//如果当前玩家在vector容器中有前继
                    J[i]->pay(*J[n-1]);
                    n--;
                }else{//没有前继
                    J[i]->pay(*J[n-1+JeueurNum]);
                    n--;
                }
            }
        }
        if(J[i]->getCount() == 1||J[i]->getCount() == 2||J[i]->getCount() == 5||J[i]->getCount() == 9
           ||J[i]->getCount() == 10){ //进行蓝卡的判定
            int n = i; //n得到当前玩家的下标
            for(int k = 0; k < JeueurNum-1;k++){//循环玩家数减1次
                if(n - 1 >= 0){ //如果当前玩家在vector容器中有前继
                    J[i]->allGet(*J[n-1]);
                    n--;
                }else{//没有前继
                    J[i]->allGet(*J[n-1+JeueurNum]);
                    n--;
                }
            }
        }
        if(J[i]->getCount() != 6){//进行绿卡的判定
            J[i]->selfGet();
        }else{ //进行紫卡的判断
            if(J[i]->isFlagOnce()){//有紫卡
                for(auto it = J[i]->begin(); it != J[i]->end();it++) {//遍历手牌
                    if (J[i]->getOnce() == "businessCenter") {//如果是商业中心
                        std::string Jname;
                        std::string jCname;
                        std::string sCname;
                        std::cout << "please enter the player you want to change with(name):" << std::endl;
                        std::cin >> Jname;
                        std::cout << "please enter the name of carte you want to get:" << std::endl;
                        std::cin >> jCname;
                        std::cout << "please enter the name of carte you want to give:" << std::endl;
                        std::cin >> sCname;
                        J[i]->changeCarte(getJeueur(Jname), getJeueur(Jname).getCarte(jCname),
                                         J[i]->getCarte(sCname));
                    } else if (J[i]->getOnce() == "gym") {//如果是体育馆
                        int n = i;//n得到当前玩家的下标
                        for (int k = 0; k < JeueurNum - 1; k++) {//循环玩家数减1次
                            if (n - 1 >= 0) {//如果当前玩家在vector容器中有前继
                                J[i]->getJeueur2(*J[n - 1]);
                                n--;
                            } else {//没有前继
                                J[i]->getJeueur2(*J[n - 1 + JeueurNum]);
                                n--;
                            }
                        }
                    } else {//如果是音乐台
                        std::string Jname;
                        std::cout << "please enter the player you want to get money from(name):" << std::endl;
                        std::cin >> Jname;
                        J[i]->getJeueur5(getJeueur(Jname));
                    }
                }
            }
        }
        afficherAll();//买卡
        std::cout<<"Dou you want to achete a carte(y/n)?"<<std::endl;
        char c;
        std::cin>>c;
        if(c == 'y'){
            std::cout<<"please enter the carte you want to buy(name):"<<std::endl;
            std::string s;
            std::cin>>s;
            J[i]->achete(s,bank);
        }
        if(win(*J[i])){//判断是否获胜
            std::cout<<"Game over !"<<std::endl;
            std::cout<<"Congratulations to "<<J[i]->getName()<<std::endl;
            flag = 1;
        }
        if(equal) //如果两个骰子掷到相同点数，该玩家再来一次
            if (J[i]->isTurnPark())
                i--;
        if(i == JeueurNum-1)
            i = -1;
        if(flag)
            return;
    }
}
void Controleur::process_dlc() {
    bool flag = 0;
    for (int i = 0; i < JeueurNum || !flag; i++) {//经过所有玩家回合
        bank.afficher();
        std::cout << "Turn of " << J[i]->getName() << std::endl;
        bool equal = J[i]->dice();//掷骰子,并得到两个骰子是否相同
        if (J[i]->getCount() == 3 || J[i]->getCount() == 9 || J[i]->getCount() == 10) { //进行红卡的判定
            int n = i;//n得到当前玩家的下标
            for (int k = 0; k < JeueurNum - 1; k++) {//循环玩家数减1次
                if (!J[i]->getMoney())
                    break;//当前玩家没有钱了，退出循环
                if (n - 1 >= 0) {//如果当前玩家在vector容器中有前继
                    J[i]->pay(*J[n - 1]);
                    n--;
                } else {//没有前继
                    J[i]->pay(*J[n - 1 + JeueurNum]);
                    n--;
                }
            }
        }
        if (J[i]->getCount() == 1 || J[i]->getCount() == 2 || J[i]->getCount() == 5 || J[i]->getCount() == 9
            || J[i]->getCount() == 10) { //进行蓝卡的判定
            int n = i; //n得到当前玩家的下标
            for (int k = 0; k < JeueurNum - 1; k++) {//循环玩家数减1次
                if (n - 1 >= 0) { //如果当前玩家在vector容器中有前继
                    J[i]->allGet(*J[n - 1]);
                    n--;
                } else {//没有前继
                    J[i]->allGet(*J[n - 1 + JeueurNum]);
                    n--;
                }
            }
        }
        if (J[i]->getCount() != 6) {//进行绿卡的判定
            J[i]->selfGet();
        } else { //进行紫卡的判断
            if (J[i]->isFlagOnce()) {//有紫卡
                for (auto it = J[i]->begin(); it != J[i]->end(); it++) {//遍历手牌
                    if (J[i]->getOnce() == "businessCenter") {//如果是商业中心
                        std::string Jname;
                        std::string jCname;
                        std::string sCname;
                        std::cout << "please enter the player you want to change with(name):" << std::endl;
                        std::cin >> Jname;
                        std::cout << "please enter the name of carte you want to get:" << std::endl;
                        std::cin >> jCname;
                        std::cout << "please enter the name of carte you want to give:" << std::endl;
                        std::cin >> sCname;
                        J[i]->changeCarte(getJeueur(Jname), getJeueur(Jname).getCarte(jCname),
                                          J[i]->getCarte(sCname));
                    } else if (J[i]->getOnce() == "gym") {//如果是体育馆
                        int n = i;//n得到当前玩家的下标
                        for (int k = 0; k < JeueurNum - 1; k++) {//循环玩家数减1次
                            if (n - 1 >= 0) {//如果当前玩家在vector容器中有前继
                                J[i]->getJeueur2(*J[n - 1]);
                                n--;
                            } else {//没有前继
                                J[i]->getJeueur2(*J[n - 1 + JeueurNum]);
                                n--;
                            }
                        }
                    } else {//如果是音乐台
                        std::string Jname;
                        std::cout << "please enter the player you want to get money from(name):" << std::endl;
                        std::cin >> Jname;
                        J[i]->getJeueur5(getJeueur(Jname));
                    }
                }
            }
        }
        afficherAll();//买卡
        std::cout << "Dou you want to achete a carte(y/n)?" << std::endl;
        char c;
        std::cin >> c;
        if (c == 'y') {
            std::cout << "please enter the carte you want to buy(name):" << std::endl;
            std::string s;
            std::cin >> s;
            J[i]->achete(s, bank);
        }
        if (win(*J[i])) {//判断是否获胜
            std::cout << "Game over !" << std::endl;
            std::cout << "Congratulations to " << J[i]->getName() << std::endl;
            flag = 1;
        }
        if (equal) //如果两个骰子掷到相同点数，该玩家再来一次
            if (J[i]->isTurnPark())
                i--;
        if (i == JeueurNum - 1)
            i = -1;
        if (flag)
            return;
    }
}

Controleur::Controleur(){
    std::cout<<"please enter the number of players(2-6):"<<std::endl;
    std::cin>>JeueurNum;
    for(int i = 0; i < JeueurNum; i++){
        std::string name = "";
        int bir;
        std::cout<<"please enter the name of player"<<i+1<<":"<<std::endl;
        std::cin>>name;
        std::cout<<"please enter the birthday of player(8 digits)"<<i+1<<":"<<std::endl;
        std::cin>>bir;
        J.push_back(new Jeueur(name,bir));
    }
}

Controleur::~Controleur() {
    Jeueur* item = nullptr;
    for(int i = 0;i < J.size();i++){
        item= J[i];
        delete item;
    }
    std::vector<Jeueur*> temp;
    J.swap(temp);
}