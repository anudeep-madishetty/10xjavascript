    // Include headers
    #include<stdio.h>
    #include<string.h>
    #include <stdio.h> 
    #include <stdlib.h> 
    #include <unistd.h>
    #define N 32  //crc-32
    char data[10000];
    char crcValue[100];
    char *gen_poly;
    int data_length,i,j;
    void XORFunction(){
        for(j = 1;j < N; j++){
            crcValue[j] = (( crcValue[j] == gen_poly[j])?'0':'1');
        }
        
    }

    void algorithm(){
        // initializing crcValue
        for(i=0;i<N;i++)
            crcValue[i]=data[i];
        do{
            // check if the first bit is 1 and calls XORFunction function
            if(crcValue[0]=='1'){
                XORFunction();
            }
        // Move the bits by 1 position for the next computation
            for(j=0;j<N-1;j++){
                crcValue[j]=crcValue[j+1];
            }
            // appending a bit from data
            crcValue[j]=data[i++];
        }while(i<=data_length+N-1);
    }



    int main()
    {
        char data[256];
        bzero(data,256);
        //reading from file
        FILE *f = fopen("encdec.outf", "rb");
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET); 
        fread(data, fsize, 1, f);
        fclose(f);
        data[fsize] = 0;
        gen_poly = "11110000111100001111000011110000";  //crc-32
        data_length=strlen(data);
        for(i=data_length;i<data_length+N-1;i++){
            data[i]='0';
        }
        algorithm();
        for(i=data_length;i<data_length+N-1;i++){
            data[i]=crcValue[i-data_length];
        }
        f = fopen("result.outf","w");
        fprintf(f,"%s", data);
        fclose(f);
            return 0;
    }
