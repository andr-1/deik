#include <iostream>
using namespace std;
#define infinity 99999
#define size 10
  
//пошук мін в масиві distance
int minD(int distance[], bool visited[]){
    int min = infinity, min_index;
    for (int v = 0; v < size; v++){
        if (visited[v] == false && distance[v] <= min){
            min = distance[v], min_index = v;
        }
    }
    return min_index;
}
  
void print(int distance[], int path[], int n, int start){
    for(int i=0;i<n;i++){
        cout<<"From "<<start+1<<" to "<<i+1<<" min distance = "<<distance[i];
        //if(distance[i]!=0) {
            cout<<endl<<"Way:   "<<i+1;
            int j=i;
            do {
                j=path[j];
                cout<<"   <-   "<<j+1;
                    
            }while(distance[j]!=0);
            //if(distance[j]!=0) cout<<"   <-   "<<0+1;
        //}
        cout<<endl<<endl;
    }
    
}
  
void deik(int** G, int start){
    int distance[size]; // вихідний масив з данними про вагу відстані до точки
    int path[size];  //масив з шляхом до кожної точки
    bool visited[size];
  
    // підготовка до початку виконання
    for (int i = 0; i < size; i++){
        distance[i] = infinity;
        visited[i] = false;
        path[i] = start;
    }
        
    //відстань до старту завжди 0
    distance[start] = 0;
  
    //виконання самого алгоритму
    for (int count = 0; count < size - 1; count++) {
        //вибираємо мінімум (на першій ітерації це завжди буде стратова вершина)
        int picked = minD(distance, visited);

        visited[picked] = true;
  
        for (int v = 0; v < size; v++){
            if (!visited[v] && G[picked][v] && distance[picked] != infinity ){
                if(distance[picked] + G[picked][v] < distance[v]){
                    distance[v] = distance[picked] + G[picked][v];
                    path[v]=picked;
                }
            }
        }                
    }
    print(distance, path, size, start);
}
  
int main(){
    int ** matrix = new int * [size];
    for (int i=0;i<size;i++){
        matrix[i] = new int [size];
        for (int j=0;j<size;j++)
            matrix[i][j]=0;
    }

    FILE *fp;
    fp=fopen("crmatdeik.txt", "r");
    for (int i=0;i<24;i++){
            int row, col, val;
            fscanf (fp,"%d ",&row);
            fscanf (fp,"%d ",&col);
            fscanf (fp,"%d ",&val);
            matrix[row-1][col-1]=val;    
    }
    fclose(fp);

    for (int i=0;i<size;i++){
        for (int j=0;j<size;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    deik(matrix,0);
    return 0;
}
