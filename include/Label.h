#include <vector>
#include "segment.h"



std::vector<int> Label(size_t t,const std::vector<segment>& S_n){
   std::vector<int> PN(S_n.size(), -1);
    if(t == 1){
        PN[8] = 1;
        PN[11] = 1;
        return PN;
    }
    else if (t == 2){
        PN[10] = 1;
        PN[11] = 1;
        return PN;
    }
    else if (t == 3){
        PN[13] = 1;
        PN[15] = 1;
        return PN;
    }
    else if (t == 4){
        PN[14] = 1;
        PN[16] = 1;
        return PN;
    }
    else if (t == 5){
        PN[16] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 6){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 7){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 8){
        PN[20] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 9){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 10){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 11){
        PN[17] = 1;
        return PN;
    }
    else if (t == 12){
        PN[18] = 1;
        return PN;
    }
    else if (t == 13){
        PN[17] = 1;
        return PN;
    }
    else if (t == 14){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 15){
        PN[16] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 16){
        PN[16] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 17){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 18){
        PN[19] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 19){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 20){
        PN[16] = 1;
        PN[14] = 1;
        return PN;
    }
    else if (t == 21){
        PN[12] = 1;
        PN[13] = 1;
        return PN;
    }
    else if (t == 22){
        PN[11] = 1;
        PN[15] = 1;
        return PN;
    }
    else if (t == 23){
        PN[8] = 1;
        PN[11] = 1;
        return PN;
    }
    else if (t == 24){
        PN[8] = 1;
        PN[12] = 1;
        return PN;
    }
    else if (t == 25){
        PN[8] = 1;
        PN[10] = 1;
        return PN;
    }
    else if (t == 26){
        PN[8] = 1;
        PN[10] = 1;
        return PN;
    }
    else if (t == 27){
        PN[7] = 1;
        PN[11] = 1;
        return PN;
    }
    else if (t == 28){
        PN[7] = 1;
        PN[9] = 1;
        return PN;
    }
    else if (t == 29){
        PN[8] = 1;
        PN[6] = 1;
        return PN;
    }
    else if (t == 30){
        PN[3] = 1;
        PN[6] = 1;
        return PN;
    }
    else if (t == 31){
        PN[3] = 1;
        PN[20] = 1;
        return PN;
    }
    else if (t == 32){
        PN[17] = 1;
        PN[21] = 1;
        return PN;
    }
    else if (t == 33){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 34){
        PN[15] = 1;
        PN[16] = 1;
        return PN;
    }
    else if (t == 35){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 36){
        PN[18] = 1;
        PN[20] = 1;
        return PN;
    }
    else if (t == 37){
        PN[17] = 1;
        PN[19] = 1;
        return PN;
    }
    else if (t == 38){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 39){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 40){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 41){
        PN[15] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 42){
        PN[18] = 1;
        return PN;
    }
    else if (t == 43){
        PN[18] = 1;
        PN[21] = 1;
        return PN;
    }
    else if (t == 44){
        PN[21] = 1;
        PN[23] = 1;
        return PN;
    }
    else if (t == 45){
        PN[1] = 1;
        PN[24] = 1;
        return PN;
    }
    else if (t == 46){
        PN[1] = 1;
        PN[22] = 1;
        return PN;
    }
    else if (t == 47){
        PN[1] = 1;
        PN[2] = 1;
        return PN;
    }
    else if (t == 48){
        PN[0] = 1;
        PN[2] = 1;
        return PN;
    }
    else if (t == 49){
        PN[24] = 1;
        PN[26] = 1;
        return PN;
    }
    else if (t == 50){
        PN[21] = 1;
        PN[22] = 1;
        return PN;
    }
    else if (t == 51){
        PN[18] = 1;
        PN[21] = 1;
        return PN;
    }
    else if (t == 52){
        PN[17] = 1;
        PN[19] = 1;
        return PN;
    }
    else if (t == 53){
        PN[15] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 54){
        PN[15] = 1;
        PN[16] = 1;
        return PN;
    }
    else if (t == 55){
        PN[18] = 1;
        PN[16] = 1;
        return PN;
    }
    else if (t == 56){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 57){
        PN[16] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 58){
        PN[17] = 1;
        PN[19] = 1;
        return PN;
    }
    else if (t == 59){
        PN[18] = 1;
        PN[16] = 1;
        return PN;
    }
    else if (t == 60){
        PN[15] = 1;
        PN[16] = 1;
        return PN;
    }
    else if (t == 61){
        PN[17] = 1;
        PN[19] = 1;
        return PN;
    }
    else if (t == 62){
        PN[14] = 1;
        PN[15] = 1;
        return PN;
    }
    else if (t == 63){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 64){
        PN[14] = 1;
        return PN;
    }
    else if (t == 65){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 66){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 67){
        PN[16] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 68){
        PN[16] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 69){
        PN[17] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 70){
        PN[15] = 1;
        PN[16] = 1;
        return PN;
    }
    else if (t == 71){
        PN[17] = 1;
        PN[19] = 1;
        return PN;
    }
    else if (t == 72){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 73){
        PN[16] = 1;
        return PN;
    }
    else if (t == 74){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 75){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 76){
        PN[17] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 77){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 78){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 79){
        PN[17] = 1;
        PN[19] = 1;
        return PN;
    }
    else if (t == 80){
        PN[15] = 1;
        PN[19] = 1;
        return PN;
    }
    else if (t == 81){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 82){
        PN[12] = 1;
        PN[16] = 1;
        return PN;
    }
    else if (t == 83){
        PN[13] = 1;
        PN[15] = 1;
        return PN;
    }
    else if (t == 84){
        PN[12] = 1;
        PN[14] = 1;
        return PN;
    }
    else if (t == 85){
        PN[12] = 1;
        PN[15] = 1;
        return PN;
    }
    else if (t == 86){
        PN[13] = 1;
        PN[15] = 1;
        return PN;
    }
    else if (t == 87){
        PN[12] = 1;
        PN[14] = 1;
        return PN;
    }
    else if (t == 88){
        PN[8] = 1;
        PN[9] = 1;
        return PN;
    }
    else if (t == 89){
        PN[6] = 1;
        PN[8] = 1;
        return PN;
    }
    else if (t == 90){
        PN[6] = 1;
        PN[8] = 1;
        return PN;
    }
    else if (t == 91){
        PN[7] = 1;
        return PN;
    }
    else if (t == 92){
        PN[4] = 1;
        PN[6] = 1;
        return PN;
    }
    else if (t == 93){
        PN[4] = 1;
        PN[23] = 1;
        return PN;
    }
    else if (t == 94){
        PN[16] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 95){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 96){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 97){
        PN[12] = 1;
        return PN;
    }
    else if (t == 98){
        PN[10] = 1;
        PN[11] = 1;
        return PN;
    }
    else if (t == 99){
        PN[11] = 1;
        PN[14] = 1;
        return PN;
    }
    else if (t == 100){
        PN[12] = 1;
        PN[14] = 1;
        return PN;
    }
    else if (t == 101){
        PN[17] = 1;
        PN[19] = 1;
        return PN;
    }
    else if (t == 102){
        PN[16] = 1;
        PN[12] = 1;
        return PN;
    }
    else if (t == 103){
        PN[11] = 1;
        PN[13] = 1;
        return PN;
    }
    else if (t == 104){
        PN[8] = 1;
        PN[11] = 1;
        return PN;
    }
    else if (t == 105){
        PN[8] = 1;
        return PN;
    }
    else if (t == 106){
        PN[9] = 1;
        PN[11] = 1;
        return PN;
    }
    else if (t == 107){
        PN[9] = 1;
        PN[14] = 1;
        return PN;
    }
    else if (t == 108){
        PN[12] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 109){
        PN[9] = 1;
        PN[13] = 1;
        return PN;
    }
    else if (t == 110){
        PN[8] = 1;
        PN[9] = 1;
        return PN;
    }
    else if (t == 111){
        PN[12] = 1;
        PN[16] = 1;
        return PN;
    }
    else if (t == 112){
        PN[15] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 113){
        PN[12] = 1;
        PN[14] = 1;
        return PN;
    }
    else if (t == 114){
        PN[12] = 1;
        PN[14] = 1;
        return PN;
    }
    else if (t == 115){
        PN[15] = 1;
        PN[16] = 1;
        return PN;
    }
    else if (t == 116){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 117){
        PN[17] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 118){
        PN[16] = 1;
        PN[18] = 1;
        return PN;
    }
    else if (t == 119){
        PN[15] = 1;
        PN[17] = 1;
        return PN;
    }
    else if (t == 120){
        PN[17] = 1;
        PN[19] = 1;
        return PN;
    }
}
