#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //get ture credit
    //just number (long)
    long CreditNumber = -1;
    do
    {
        CreditNumber = get_long("enter credit number: ");
    }
    while (CreditNumber < 0);

    //while sum even number
    //get even number
    //sum even number
    //for part part number
    long CreditNumber2 = CreditNumber;
    int SumEvenNumber = 0;
    long x;
    int counter = 0;
    while (CreditNumber2 > 0)
    {
        CreditNumber2 = floor(CreditNumber2 / 10);
        counter++;
    }



    //while sum even number
    //get even number
    //sum even number
    //for part part number
    CreditNumber2 = CreditNumber;
    SumEvenNumber = 0;
    CreditNumber2 = floor(CreditNumber2 / 10);
    x = 0;
    if ((CreditNumber2 % 10) * 2 > 10)
    {
        x = floor((CreditNumber2 % 10) * 2 / 10);
        SumEvenNumber = SumEvenNumber + ((CreditNumber2 % 10) * 2) % 10 + x % 10;
    }
    else
    {
        SumEvenNumber = SumEvenNumber + (CreditNumber2 % 10) * 2;
    }
    while (CreditNumber2 > 0)
    {
        CreditNumber2 = floor(CreditNumber2 / 100);
        if ((CreditNumber2 % 10) * 2 >= 10)
        {
            x = floor((CreditNumber2 % 10) * 2 / 10);
            SumEvenNumber = SumEvenNumber + ((CreditNumber2 % 10) * 2) % 10 + x % 10;
        }
        else
        {
            SumEvenNumber = SumEvenNumber + (CreditNumber2 % 10) * 2;
        }
        //printf("%i\n", SumEvenNumber);
    }

    //while sum odd number
    //get odd number
    //sum number
    int SumOddNumber = 0;
    CreditNumber2 = CreditNumber;
    while (CreditNumber2 > 0)
    {
        SumOddNumber = SumOddNumber + CreditNumber2 % 10;
        CreditNumber2 = floor(CreditNumber2 / 100);
    }
    //2first number
    CreditNumber2 = CreditNumber;
    int N1, N2, TFirstN, i = 0;
    while (CreditNumber2 > 0)
    {
        if (i % 2 == 0)
        {
            N1 = CreditNumber2 % 10;
        }
        else
        {
            N2 = CreditNumber2 % 10;
        }
        CreditNumber2 = floor(CreditNumber2 / 10);
        i++;
    }
    if (i % 2 == 0)
    {
        TFirstN = N2 * 10 + N1;
    }
    else
    {
        TFirstN = N2 + N1 * 10;
    }
    //is credit??
    //sum odd + even*2
    int sum = SumEvenNumber + SumOddNumber;
    //(for test) printf("even: %i\nodd: %i\nsum: %i\nTFN: %i\ncounter: %i\n",SumEvenNumber ,SumOddNumber ,sum ,TFirstN ,counter);

    //is last number 0??
    if (sum % 10 == 0)
    {
        if (counter == 15 && (TFirstN == 34 || TFirstN == 37))
        {
            printf("AMEX\n");
        }
        else if (counter == 16 && (TFirstN == 51 || TFirstN == 52 || TFirstN == 53 || TFirstN == 54 || TFirstN == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((counter == 16 || counter == 13) && round(TFirstN / 10) == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}