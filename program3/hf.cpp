
    int size=0;
    std::vector<int> av;
    std::vector<int> av1;
    std::vector<int> av2;
    int res1=0;
    int res2=0;
    int res3=0;
    for(int i=0;i<ins.length();i++){
        size= (size *31 + (((int) ins[i])))%3;

    }
//cout << size << endl;
    for(int vind=0;vind<2;vind++){
        av.push_back((int) ins[vind]);

    }

    for(int vind2=2;vind2<4;vind2++){
        av1.push_back((int) ins[vind2]);
    }

        av2.push_back((int) ins[4]);

    for(int vind=0;vind<2;vind++){
    res1 = (res1 + (av[vind])*(63))*17; //17
    }
    for(int vind2=0;vind2<2;vind2++){
   res2 = ((res2 + (av1[vind2])*47)*23); //23
    }

    res3= (((av2[0] *53)%59)*3);
    int total= (res1 + res2 + res3);
    int res = (total) + HASH_TABLE_SIZE;

    int h1 =  (res % HASH_TABLE_SIZE);

    //cout << h1 << endl;

       return h1;
    //return size%HASH_TABLE_SIZE;
