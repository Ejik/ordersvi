#ifndef INDICATORSMODEL_H
#define INDICATORSMODEL_H

class IndicatorsModel {
private:
    int amount;
    int sum;
    int cash;
    int nAmount;
    int nSum;
    int nCash;
public:
    IndicatorsModel() { amount = 0; sum = 0; cash = 0; nAmount = 0; nSum  = 0; nCash = 0; }
    int getAmount() { return amount; }
    int getSum() { return sum; }
    int getCash() { return cash; }
    int getNAmount() { return nAmount; }
    int getNSum() { return nSum; }
    int getNCash() {return nCash; }


    void setAmount(int value) { amount = value; }
    void setSum(int value) { sum = value; }
    void setCash(int value) { cash = value; }
    void setNAmount(int value) { nAmount = value; }
    void setNSum(int value) { nSum = value; }
    void setNCash(int value) { nCash = value; }

    int getAmountPersent() {
        if (nAmount == 0) { return 0; }
        return amount * 100 / nAmount;
    }

    int getSumPersent() {
        if (nSum == 0) { return 0; }
        return sum * 100 / nSum;
    }

    int getCashPersent() {
        if (nCash == 0) { return 0; }
        return cash * 100 / nCash;
    }

};

#endif // INDICATORSMODEL_H
