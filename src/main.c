///sddssddsd
#include<stdio.h>
#include<stdlib.h>
      //sss
char notKeyword(FILE *file, char charNow){

    char lastChar;
    int countOrNot=0;
    if(charNow == '='){
        while ((charNow = fgetc(file)) != EOF){
            if(charNow == '"' || charNow == '\''){
                countOrNot = 1;
            }
            if(isalpha(charNow) && !isdigit(lastChar) && countOrNot==0){
                return charNow;
            }
            else if(charNow == ';' || charNow == '\n' || charNow == ')')
                break;
            lastChar = charNow;
        }
    }

    else if (charNow == '%'){
        while ((charNow = fgetc(file)) != EOF){
            if(charNow == '"' || charNow == '\n' || charNow == ')' || charNow == ' ' || charNow == ';')
                break;
        }
    }

    else if(charNow == '"'){
          while ((charNow = fgetc(file)) != EOF){
            if(charNow == '"' || charNow == '\n' || charNow == ')')
                break;
        }
    }

    else if(charNow == '\''){
          while ((charNow = fgetc(file)) != EOF){
            if(charNow == '\'' || charNow == '\n' || charNow == ')')
                break;
        }
    }
//Avoid counting comments
    else if(charNow == '/'){

        int doubleSlash = 0, starSlash = 4;
        while ((charNow = fgetc(file)) != EOF){
            if(charNow == '/'){
                doubleSlash = 1;

            }
            else if(charNow == '*'){
                starSlash= 2;
                break;
            }
            else if(doubleSlash == 1 && charNow == '\n')
                break;

        }
        if(starSlash == 2){
            while ((charNow = fgetc(file)) != EOF){
                if(charNow == '*')
                    starSlash = 1;
                else if(charNow == '/' && starSlash==1)
                    break;
            }
        }
    }
}

int main(int argc, char **argv){

    FILE *file = fopen(argv[1], "r");
    char charNow,lastChar;
    int totalNumber =0,countOrNot =1,countOrNot2=0, flagSlash =0, cCount=0;
    int  position=0,quotesOnOff =0,sOnOf = 0, charSeek,lines=0, i=0,wrong=0,flag=0;
    if (file == NULL)
        return printf("Invalid file");

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);

    int code[size];

    while ((charNow = fgetc(file)) != EOF){
        cCount++;
        if(charNow == '\n')
            lines++;
        if(charNow == '=' || charNow == '%' || charNow =='/' || charNow =='"'  || charNow == '\''){
                if((isalpha(lastChar) || isdigit(lastChar)) && charNow == '='){
                    totalNumber++;
                    flag=1;
                }
                charNow = notKeyword(file, charNow);
        }

        if(isalpha(charNow)){
            countOrNot2 = 1;
        }

        if(!isalpha(lastChar) && isdigit(charNow)){
            countOrNot =0;
        }

        else if ((isalpha(charNow) || isdigit(charNow) || charNow == '_') && (cCount != size-lines)){
            lastChar = charNow;
            countOrNot =1;
        }

        else if((isdigit(lastChar) || isalpha(lastChar) || lastChar == '_') && (!isalpha(charNow) || !isdigit(charNow) || cCount == size-lines)){
            lastChar = charNow;
            if((countOrNot == 1 ||  countOrNot2 == 1) && flag==0){
                flag==0;
                totalNumber++;
            }
        }
        flag=0;
        if(!isalpha(charNow) && !isdigit(charNow)){
            countOrNot2= 0;
        }
    }

    printf("\nTotal of keywords and definers: %d",totalNumber);
    rewind(file);
    cCount = 0;
    lines = 0;

    int flag7=0,flagP=0,flagC=0,flagB=0;
    int flagP2=0,flagC2=0,flagB2=0;
    int wrong1=0,wrong2=0,wrong3=0, doubleSlash=0;
    char lChar = 'b';
    while ((charNow = fgetc(file)) != EOF){
        cCount++;
        if((flagSlash == 1 || sOnOf == 1) && (isalpha(charNow) || isdigit(charNow))){
            doubleSlash=0;
            flagSlash =0;
        }
        else if((sOnOf == 1 || quotesOnOff == 1) && (charNow == '\\')){
                doubleSlash++;
                flagSlash=1;

        }
        else if((sOnOf == 1 || quotesOnOff == 1) && (charNow == ';' || charNow == '\n' )) {
            if(sOnOf == 1 && charNow != ';' && charNow != ')' && lChar != '\\'){
                printf("\n You have more or less ' than necessary ");
                wrong = 1;
                position--;
                sOnOf =0;
            }
            else if(quotesOnOff ==1 && lChar != '\\'){
                printf("\n You have more or less \" than necessary ");
                wrong = 1;
                position--;
                quotesOnOff =0;
            }
        }
        switch (charNow){
            case '(':
                if(quotesOnOff != 1 && sOnOf != 1){
                    flagC++;
                    code[position] = 1;
                    position++;
                }
                break;

            case '[':
                if(quotesOnOff != 1 && sOnOf != 1){
                    flagB++;
                    code[position] = 5;
                    position++;
                }
                break;

            case '{':
                if(quotesOnOff != 1 && sOnOf != 1){
                    flagP++;
                    code[position] = 3;
                    position++;
                }
                break;

            case '"':
                if(flagSlash == 1 && doubleSlash == 1){
                    flagSlash=0;
                    break;
                }
                if(quotesOnOff == 1 && flagSlash == 0 && lChar != '\\' || (quotesOnOff==1 && doubleSlash == 2)){
                    doubleSlash=0;
                    position--;
                    quotesOnOff =0;
                    break;
                }
                else if(sOnOf == 0 && lChar != '\\'){
                    quotesOnOff = 1;
                    code[position] = 7;
                    position++;
                    break;
                }
                break;

            case '\'':
                if(flagSlash == 1 && doubleSlash == 1){
                    flagSlash=0;
                    break;
                }
                else if((sOnOf == 1 && flagSlash == 0) || (sOnOf==1 && doubleSlash==2)){
                    doubleSlash=0;
                    position--;
                    sOnOf =0;
                    break;
                }
                else if (quotesOnOff == 0  && lChar != '\\'){
                    sOnOf = 1;
                    code[position] = 8;
                    position++;
                    break;
                }
                break;

            case ')':
               if(quotesOnOff != 1 && sOnOf != 1){
                    flagC2++;
                    while(flag7 ==0){
                        if(code[position-1]+1 == 2){
                            flag7 == 1;
                            position--;
                            break;
                        }
                        else if(code[position-1]+1 == 6){
                            wrong2 += 1;
                            position--;
                        }
                        else  if(code[position-1]+1 == 4){
                            wrong3 += 1;
                            position--;
                        }
                        else  if(code[position-1] == 7){
                            wrong = 1;
                            position--;
                        }
                        else if(position == 0){
                            break;
                        }
                    }
                    break;
                }
                break;

            case ']':
                if(quotesOnOff != 1 && sOnOf != 1){
                        flagB2++;
                    while(flag7 ==0){
                        if(code[position-1]+1 == 6){
                            flag7 == 1;
                            position--;
                            break;
                        }
                        else if(code[position-1]+1 == 4){
                            wrong3 += 1;
                            position--;
                        }
                        else  if(code[position-1]+1 == 2){
                            wrong1 += 1;
                            position--;
                        }
                        else  if(code[position-1] == 7){
                            wrong = 1;
                            position--;
                        }
                        else if(position == 0){
                            wrong2++;
                            break;
                        }
                    }
                    break;
                }
                break;
            case '}':
                if(quotesOnOff != 1  && sOnOf != 1){
                    flagP2++;
                    while(flag7 ==0){
                        if(code[position-1]+1 == 4){
                            flag7 == 1;
                            position--;
                            break;
                        }
                        else if(code[position-1]+1 == 2){
                            wrong1 += 1;
                            position--;
                        }
                        else  if(code[position-1]+1 == 6){
                            wrong2 = 1;
                            position--;
                        }
                        else  if(code[position-1] == 7){
                            wrong = 1;
                            position--;
                        }
                        else if(position <= 0){
                            wrong3++;
                            break;
                        }
                    }
                }
        }
        lChar = charNow;
    }


    if(position == 0 && (wrong2==0 && wrong1==0&& wrong3==0 && wrong==0)){
        printf("\nEverything is fine with all the {} [] () \" '");
    }

    if(wrong1 >=1 && flagC == flagC2){
        printf("\nWrong nested (), exactly %d pairs",wrong1);
    }
    else if(wrong1 >=1 && flagC != flagC2){
        if(flagC> flagC2){
            printf("\nYou have less ) than necessary, exactly: %d",flagC-flagC2);
        }
        else{
            printf("\nYou have more ) than necessary, exactly: %d",flagC2-flagC);
        }
    }

     if(wrong2 >= 1 && flagB ==flagB2){
        printf("\nWrong nested [], exactly %d pairs");
     }
     else if(wrong2 >= 1 && flagB != flagB2){
        if(flagB> flagB2){
                printf("\nYou have less ] than necessary, exactly: %d",flagB-flagB2);
            }
            else{
                printf("\nYou have more ] than necessary, exactly: %d",flagB2-flagB);
            }
         }

     if(wrong3 >= 1 && flagP == flagP2){
        printf("\nWrong nested {}, exactly %d pairs");
     }
     else if((position!=0 || wrong3 >= 1) && flagP != flagP2){
        if(flagP> flagP2){
            printf("\nYou have less } than necessary, exactly: %d",flagP-flagP2);
        }
        else{
            printf("\nYou have more } than necessary, exactly: %d",flagP2-flagP);
        }
     }

    return 0;
}

