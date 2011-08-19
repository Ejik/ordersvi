#ifndef INDICATORSMODEL_H
#define INDICATORSMODEL_H

class IndicatorsModel {
private:
    int amount;
    int sum;
    int cash;
public:
    IndicatorsModel() { amount = 0; sum = 0; cash = 0; }
    int getAmount() { return amount; }
    int getSum() { return sum; }
    int getCash() { return cash; }

    void setAmount(int value) { amount = value; }
    void setSum(int value) { sum = value; }
    void setCash(int value) { cash = value; }
};

#endif // INDICATORSMODEL_H
