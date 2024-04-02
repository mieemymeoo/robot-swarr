#include<iostream>
#include<fstream>
#include <ctime>
#include <cstdlib>
#include<iomanip>
using namespace std;

struct matrix{
    int **a;
    int row;
    int col;
};

struct robot{
    int x;
    int y;
    int *kq;
    int n;
};
void input(matrix &m) {
    cout << "Nhap cac phan tu cua mang 2D:" << endl;
    for (int i = 0; i < m.row; i++) {
        for (int j = 0; j < m.col; j++) {
            cout<<"["<<i<<"]"<<"["<<j<<"]: ";cin >> m.a[i][j];
        }
    }
}
void inputl1(matrix &m)
{
    srand(time(0));
    int size = m.row * m.col;
    int mp[size];
    for (int i = 0; i < size; i++) {
        mp[i] = i % 30 + 1;
    }

    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(mp[i], mp[j]);
    }

    int index = 0;
    for (int i = 0; i < m.row; i++) {
        for (int j = 0; j < m.col; j++) {
            m.a[i][j] = mp[index];
            index++;
        }
    }
}
void inputl2(matrix &m)
{
    srand(time(0));
    int size = m.row * m.col;
    int mp[size];
    for (int i = 0; i < size; i++) {
        mp[i] = i % 80 + 1;
    }

    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(mp[i], mp[j]);
    }

    int index = 0;
    for (int i = 0; i < m.row; i++) {
        for (int j = 0; j < m.col; j++) {
            m.a[i][j] = mp[index];
            index++;
        }
    }
}

void inputl3(matrix &m)
{
    srand(time(0));
    int size = m.row * m.col;
    int mp[size];
    for (int i = 0; i < size; i++) {
        mp[i] = i % 101 + 50;
    }

    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(mp[i], mp[j]);
    }

    int index = 0;
    for (int i = 0; i < m.row; i++) {
        for (int j = 0; j < m.col; j++) {
            m.a[i][j] = mp[index];
            index++;
        }
    }
}

void output(matrix &m, ofstream &outfile)
{
	cout<<"Mang 2D vua nhap: "<<endl;
	outfile<<"Mang 2D ban da nhap:"<<endl;
	for(int i=0;i<m.row;i++)
	{
		for (int j=0;j<m.col;j++)
		{
			cout<<setw(3)<<m.a[i][j]<<"   ";
			outfile<<m.a[i][j]<<" ";
		}
	cout<<endl;
	outfile<<endl;
	}
}
int robotpath(matrix m, robot &r, ofstream &outfile) {
	matrix copya;
	copya.row=m.row;
	copya.col=m.col;
	copya.a=new int*[copya.row];
	for(int i=0;i<copya.col;i++)
	{
		copya.a[i]=new int[copya.col];
	}
	
	for(int i=0;i<copya.row;i++)
	{
		for(int j=0;j<copya.col;j++)
		{
			copya.a[i][j]=m.a[i][j];
		}
	}
	    
    r.n = 0;
    cout<<"Nhap vi tri cua robot: "; cin>>r.x>>r.y;
    cout<<"Duong di cua robot: "<<endl; 
    while (true) {
        int max = -1;
        int nextX = r.x, nextY = r.y;
        r.kq[r.n] = m.a[r.x][r.y];
        r.n++;
        cout<<"-->"<<copya.a[r.x][r.y]<<" "; 
    	outfile<<copya.a[r.x][r.y]<<" "; 
        // up
        if (r.x > 0 && copya.a[r.x - 1][r.y] > max ) 
        { 
            max = copya.a[r.x - 1][r.y];
            nextX= r.x - 1;
            nextY = r.y;
        }
        // down
        if (r.x < m.row - 1 && copya.a[r.x + 1][r.y] > max  ) 
        {    
            max = copya.a[r.x + 1][r.y];
            nextX = r.x + 1;
            nextY = r.y;
        }

        // left
        if (r.y > 0 && copya.a[r.x][r.y - 1] > max  ) 
        {
            max = copya.a[r.x][r.y - 1];
            nextX = r.x;
            nextY = r.y - 1;
        }

        // right
        if (r.y < m.col - 1 && copya.a[r.x][r.y + 1] > max ) 
        {
            max = copya.a[r.x][r.y + 1];
            nextX = r.x;
            nextY = r.y + 1;
        }
    cout<<endl;
    for(int i=0;i<copya.row;i++)
	{
    	for(int j=0;j<copya.col;j++)
    	{
        	if (i == r.x && j == r.y) {
            	cout<<"\033[31m"<<copya.a[i][j]<<"\033[0m ";
        	}else {
            cout<<copya.a[i][j]<<" ";
        }
    }
    cout<<endl;
	}
	cout<<endl;
        if (max == -1) break;
        copya.a[r.x][r.y] = -1;
        r.x = nextX;
        r.y = nextY;
    }
    
    
    for (int i = 0; i < m.row; i++) {
        delete[] copya.a[i];
    }
    delete[] copya.a;

    return r.n;
}


int intersect(matrix m, robot &r1,robot &r2, ofstream &outfile) {
    cout<<"Robot 1:";
    robotpath(m, r1, outfile);
    cout<<endl;
    cout<<"Robot 2: ";
    robotpath(m, r2, outfile);
    int count=0;
    cout<<endl<<"Cac diem  giao nhau cua 2 robot: "<<endl;
    outfile<<endl<<"Cac diem  giao nhau cua 2 robot: "<<endl;
    for(int i=0;i<r1.n;i++)
    {
        for(int j=0;j<r2.n;j++)
        {
            if (r1.kq[i]==r2.kq[j])
            {
                count++;
                cout<<r1.kq[i]<<" ";
                outfile<<r1.kq[i]<<" ";
                break;
            }
        }
    }
    cout<<endl;
    cout<<"So vi tri giao nhau cua 2 Robot: "<<count;
    outfile<<endl<<"So vi tri giao nhau cua 2 Robot: "<<count;
}

int whowin(matrix &m, int ax, int ay, int bx, int by, ofstream &outfile) {
    matrix copya;
    copya.row=m.row;
    copya.col=m.col;
    copya.a=new int*[copya.row];
    for(int i=0;i<copya.row;i++)
    {
    	copya.a[i]=new int[copya.col];
	}
	
	for (int i=0;i<copya.row;i++)
	{
		for (int j=0;j<copya.col;j++)
		{
			copya.a[i][j]=m.a[i][j];
		}
	}
    int sumA = copya.a[ax][ay];
    int sumB = copya.a[bx][by];

    copya.a[ax][ay] = -1;
    copya.a[bx][by] = -1;

    while (true) {
        int maxA = -1;
        int nextAx = ax;
        int nextAy = ay;
        if (ax > 0 && copya.a[ax-1][ay] > maxA) 
		{
            maxA = copya.a[ax-1][ay];
            nextAx = ax-1;
            nextAy = ay;
        }
        if (ax < copya.row-1 && copya.a[ax+1][ay] > maxA) 
		{
            maxA = copya.a[ax+1][ay];
            nextAx = ax+1;
            nextAy = ay;
        }
        if (ay > 0 && copya.a[ax][ay-1] > maxA) 
		{
            maxA = copya.a[ax][ay-1];
            nextAx = ax;
            nextAy = ay-1;
        }
        if (ay < copya.col-1 && copya.a[ax][ay+1] > maxA) 
		{
            maxA = 	copya.a[ax][ay+1];
        	nextAx = ax;
            nextAy = ay+1;
        }

        int maxB = -1;
        int nextBx = bx;
        int nextBy = by;
        if (bx > 0 && copya.a[bx-1][by] > maxB) 
		{
            maxB = copya.a[bx-1][by];
            nextBx = bx-1;
            nextBy = by;
        }
        if (bx <copya.row-1 && copya.a[bx+1][by] > maxB) 
		{
            maxB = copya.a[bx+1][by];
            nextBx = bx+1;
            nextBy = by;
        }
        if (by > 0 && copya.a[bx][by-1] > maxB) 
		{
            maxB = copya.a[bx][by-1];
            nextBx = bx;
            nextBy = by-1;
        }
        if (by < copya.col - 1 && copya.a[bx][by+1] > maxB) 
		{
            maxB = copya.a[bx][by+1];
            nextBx = bx;
            nextBy = by+1;
        }


        if (maxA == -1 && maxB == -1) break;
			for(int i=0;i<copya.row;i++)
			{
    			for(int j=0;j<copya.col;j++)
    			{
        			if (i == ax && j == ay) {
            			cout<<"\033[31m"<<copya.a[i][j]<<"\033[0m ";
        			} 
        			else if (i == bx && j == by) {
            			cout<<"\033[34m"<<copya.a[i][j]<<"\033[0m ";
        			}else {
            			cout<<copya.a[i][j]<<" ";
        	}
    		}		
    	cout<<endl;
		}
		cout << "Tong trong so cua Robot A: " << "\033[31m"<<sumA<<"\033[0m " << endl;
		cout << "Tong trong so cua Robot B: " << "\033[34m"<<sumB <<"\033[0m"<< endl;
		cout<<endl;
        if (maxA != -1) 
		{
            ax = nextAx;
            ay = nextAy;
            sumA += maxA;
            copya.a[ax][ay] = -1; 

        }

        if (maxB != -1) {
            bx = nextBx;
            by = nextBy;
            sumB += maxB;
            copya.a[bx][by] = -1; 

        }

    }
    cout<<"----------------------------------------------------"<<endl;
    outfile << "Tong trong so cua Robot A: " << sumA << endl;
    cout << "Tong trong so cua Robot A: " << sumA << endl;
    outfile << "Tong trong so cua Robot B: " << sumB << endl;
    cout << "Tong trong so cua Robot B: " << sumB << endl;

    
	if(sumA>sumB)
	{
		cout<<"A thang!";
		outfile<<"A thang!";
	}
	else if(sumA<sumB)
	{
		cout<<"B thang!";
		outfile<<"B thang!";
	}
	else
	{ 
		cout<<"Hoa";
		outfile<<"Hoa!";
	}

	for(int i=0;i<copya.row;i++)
	{
		delete[] copya.a[i];	
	}
	delete[] copya.a;
}


int main() {
	matrix m;
    int mode;
    char exitkey;
    int exitgame = 0;
	ofstream outfile("lichsugame.txt", ios::app);
    while (exitgame==0) {
        cout << "Chon che do choi (1, 2, or 3): "<<endl;
        cout<<"1. PVP"<<endl;
        cout<<"2. PVE"<<endl;
        cout<<"3. Huong dan(p3)"<<endl;
        cin >> mode;
        switch (mode) {
            case 1:
            	while(true){
				
                cout << "Ban dang trong che do 1" << endl;
                int p1;
            	cout << "1.Nhap ma tran" << endl;
		        cout << "2.Tim quang duong cua robot trong ma tran" << endl;
		        cout << "3.Tim so vi tri giao nhau cua 2 robot khi dat o 2 vi tri" << endl;
		        cout << "4.Tim tong trong so lon nhat trong 2 robot A or B" << endl;
		        cout << "-------------------------------------------------------" << endl;
                cout << "Chon chuc nang: ";
                cin >> p1;
                if (p1 == 1) {
                    cout << "Ban dang trong chuc nang 1" << endl;
            		cout << "Nhap so hang: ";
		            cin >> m.row;
		            cout << "Nhap so cot: ";
		            cin >> m.col;
		            m.a = new int*[m.row];
		            for (int i = 0; i < m.row; i++)
		            {
		                m.a[i] = new int[m.col];
		            }
		            input(m);
		            output(m, outfile);
		            cout << endl;
                } else if (p1 == 2) {
                    cout << "Ban dang trong chuc nang 2" << endl;
            		cout << "2.Tim quang duong cua robot trong ma tran" << endl;
		            robot r;
		            r.kq = new int[m.row * m.col];
		            outfile << "Ket qua : " << endl;
		            robotpath(m, r, outfile);
		            outfile << endl;
		            delete[] r.kq;
		            cout << endl;
		    	} else if(p1==3){
		    		cout << "Ban dang trong chuc nang 3" << endl;
    				cout << "3.Tim so vi tri giao nhau cua 2 robot khi dat o 2 vi tri" << endl;
		            robot r1, r2;
		            r1.kq = new int[m.row * m.col];
		            r2.kq = new int[m.row * m.col];
		            outfile << "Ket qua :" << endl;
		            intersect(m, r1, r2, outfile);
		            outfile << endl;
		            delete[] r1.kq, r2.kq;
		            cout << endl;	
				} else if(p1==4){
					cout << "4.Tim tong trong so lon nhat trong 2 robot A or B" << endl;
		            int ax, ay, bx, by;
		            cout << "Nhap vi tri cua Robot A: ";
		            cin >> ax >> ay;
		            cout << "Nhap vi tri cua Robot B: ";
		            cin >> bx >> by;
		            outfile << "Ket qua cua che do :" << endl;
		            whowin(m, ax, ay, bx, by, outfile);
		            cout << endl;
				}
            
                 else {
                    cout << "Khong co chuc nang nay" << endl;
                }
                cout << "Bam 'x' de thoat che do : ";
                cin >> exitkey;
                if (exitkey == 'x') {
                    cout << "Da thoat che do " <<mode<< endl;
                    break;
                }
            }
            break;
            case 2:
            	while(true){
                cout << "Ban dang trong che do 2" << endl;
                int p2;
                cout<<"Chon muc do choi: "<<endl; 
				cout<<"Muc 1: De"<<endl; 
				cout<<"Muc 2: Binh thuong"<<endl; 
				cout<<"Muc 3: Kho"<<endl;
                cin >> p2;
              switch (p2) {
                    case 1:
                    	while(true){
                        cout << "Ban chon muc 1" << endl;
                        int p1_2;
						cout << "1.Nhap ma tran" << endl;
				        cout << "2.Tim quang duong cua robot trong ma tran" << endl;
				        cout << "3.Tim so vi tri giao nhau cua 2 robot khi dat o 2 vi tri" << endl;
				        cout << "4.Tim tong trong so lon nhat trong 2 robot A or B" << endl;
				        cout << "5.Thoat  che do 1" << endl;
				        cout << "-------------------------------------------------------" << endl;
		                cout << "Chon chuc nang: ";
                        cin >> p1_2;
                        if (p1_2==1) {
							 cout << "Ban chon chuc nang 1"<<endl;
							int selectp1_2;
							cout<<"Tu nhap (p1): "<<endl;
							cout<<"May nhap (p2): "<<endl;
							cin>>selectp1_2;
							while(true){
							if(selectp1_2==1){
							cout<<"Ban chon tu nhap : "<<endl;
                        	cout << "Nhap so hang: ";
						    cin >> m.row;
						    cout << "Nhap so cot: ";
						    cin >> m.col;
						    m.a = new int*[m.row];
						    for (int i = 0; i < m.row; i++)
						    {
						        m.a[i] = new int[m.col];
						    }
						
						    inputl1(m); 
						    output(m, outfile);
							cout<<endl<<"Ma tran: "<<m.row<<"x"<<m.col<<endl;
							} if(selectp1_2==2)
							{
								cout<<"Ban chon may nhap:"<<endl;
								srand(time(0));
								m.row = rand() % 3+3;
								m.col = rand() % 4+3;
							m.a = new int*[m.row];
						    for (int i = 0; i < m.row; i++)
						    {
						        m.a[i] = new int[m.col];
						    }
						
						    inputl1(m); 
						    output(m, outfile);
							cout<<endl<<"Ma tran: "<<m.row<<"x"<<m.col<<endl;
							}
							cout << "Bam 'x' de thoat : ";
                			cin >> exitkey;
                			if (exitkey == 'x') {
                				
                    			cout << "Da thoat  "<<endl;
                    			break;
                				}
							}

						    cout << endl;
						} else if(p1_2==2){
							cout<<"Ban chon chuc nang 2"<<endl;
							cout << "2.Tim quang duong cua robot trong ma tran" << endl;
				            robot r;
				            r.kq = new int[m.row * m.col];
				            outfile << "Ket qua : " << endl;
				            robotpath(m, r, outfile);
				            outfile << endl;
				            delete[] r.kq;
				            cout << endl;
				    	} else if(p1_2==3){
				    		cout<<"Ban chon chuc nang 3"<<endl;
			    			cout << "3.Tim so vi tri giao nhau cua 2 robot khi dat o 2 vi tri" << endl;
				            robot r1, r2;
				            r1.kq = new int[m.row * m.col];
				            r2.kq = new int[m.row * m.col];
				            outfile << "Ket qua :" << endl;
				            intersect(m, r1, r2, outfile);
				            outfile << endl;
				            delete[] r1.kq, r2.kq;
				            cout << endl;
						} else if(p1_2==4){
							cout<<"Ban chon chuc nang 4"<<endl;
							cout << "4.Tim tong trong so lon nhat trong 2 robot A or B" << endl;
				            int ax, ay, bx, by;
				            cout << "Nhap vi tri cua Robot A: ";
				            cin >> ax >> ay;
				           	srand(time(0));
							bx = rand() % m.row;
							by = rand() % m.col;
							cout<<"Vi tri cua Robot B: ";
							cout<<bx<<" "<<by<<endl;
				            outfile << "Ket qua  :" << endl;
				            whowin(m, ax, ay, bx, by, outfile);
				            cout << endl;
								
                    	} else {
                            cout << "Khong co chuc nang nay" << endl;
                        }
                            cout << "Bam 'x' de thoat muc 1 : ";
                			cin >> exitkey;
                			if (exitkey == 'x') {
                				
                    			cout << "Da thoat muc  " <<p1_2<< endl;
                    			break;
                				}
                        
                    } break;
                    case 2:
                    	while(true){
                    	cout << "Ban chon muc 2" << endl;
                        int p2_2;
						cout << "1.Nhap ma tran" << endl;
				        cout << "2.Tim quang duong cua robot trong ma tran" << endl;
				        cout << "3.Tim so vi tri giao nhau cua 2 robot khi dat o 2 vi tri" << endl;
				        cout << "4.Tim tong trong so lon nhat trong 2 robot A or B" << endl;
				        cout << "-------------------------------------------------------" << endl;
		                cout << "Chon chuc nang: ";
                        cin >> p2_2;
						if(p2_2==1){
							cout << "Ban chon chuc nang 1"<<endl;
							int selectp2_2;
							cout<<"Tu nhap (p1): "<<endl;
							cout<<"May nhap (p2): "<<endl;
							cin>>selectp2_2;
							while(true){
							if(selectp2_2==1){
							cout<<"Ban chon tu nhap : "<<endl;
                        	cout << "Nhap so hang: ";
						    cin >> m.row;
						    cout << "Nhap so cot: ";
						    cin >> m.col;
						    m.a = new int*[m.row];
						    for (int i = 0; i < m.row; i++)
						    {
						        m.a[i] = new int[m.col];
						    }
						
						    inputl2(m); 
						    output(m, outfile);
							cout<<endl<<"Ma tran: "<<m.row<<"x"<<m.col<<endl;
							} if(selectp2_2==2)
							{
								cout<<"Ban chon may nhap:"<<endl;
								srand(time(0));
								m.row = rand() % 5+4;
								m.col = rand() % 8+3;
							m.a = new int*[m.row];
						    for (int i = 0; i < m.row; i++)
						    {
						        m.a[i] = new int[m.col];
						    }
						
						    inputl2(m); 
						    output(m, outfile);
							cout<<endl<<"Ma tran: "<<m.row<<"x"<<m.col<<endl;
							}
							cout << "Bam 'x' de thoat : ";
                			cin >> exitkey;
                			if (exitkey == 'x') {
                				
                    			cout << "Da thoat  "<<endl;
                    			break;
                				}
							}
						    cout << endl;
						} else if(p2_2==2){
							cout<<"Ban chon chuc nang 2"<<endl;
							cout << "2.Tim quang duong cua robot trong ma tran" << endl;
				            robot r;
				            r.kq = new int[m.row * m.col];
				            outfile << "Ket qua : " << endl;
				            robotpath(m, r, outfile);
				            outfile << endl;
				            delete[] r.kq;
				            cout << endl;
				    	} else if(p2_2==3){
				    		cout<<"Ban chon chuc nang 3"<<endl;
			    			cout << "3.Tim so vi tri giao nhau cua 2 robot khi dat o 2 vi tri" << endl;
				            robot r1, r2;
				            r1.kq = new int[m.row * m.col];
				            r2.kq = new int[m.row * m.col];
				            outfile << "Ket qua :" << endl;
				            intersect(m, r1, r2, outfile);
				            outfile << endl;
				            delete[] r1.kq, r2.kq;
				            cout << endl;
						} else if(p2_2==4){
							cout<<"Ban chon chuc nang 4"<<endl;
							cout << "4.Tim tong trong so lon nhat trong 2 robot A or B" << endl;
				            int ax, ay, bx, by;
				            cout << "Nhap vi tri cua Robot A: ";
				            cin >> ax >> ay;
							srand(time(0));
							bx = rand() % m.row;
							by = rand() % m.col;
							cout<<"Vi tri cua Robot B: ";
							cout<<bx<<" "<<by<<endl;
				            outfile << "Ket qua :" << endl;
				            whowin(m, ax, ay, bx, by, outfile);
				            cout << endl;
								
                    	} else {
                            cout << "Khong co chuc nang nay" << endl;
                        }
                            cout << "Bam 'x' de thoat muc 2 : ";
                			cin >> exitkey;
                			if (exitkey == 'x') {
                    			cout << "Da thoat muc " <<p2_2<< endl;
                    			break;
                				}
					} break;
                    case 3:
                    	while(true){
						cout << "Ban chon muc 3" << endl;
                        int p3_2;
						cout << "1.Nhap ma tran" << endl;
				        cout << "2.Tim quang duong cua robot trong ma tran" << endl;
				        cout << "3.Tim so vi tri giao nhau cua 2 robot khi dat o 2 vi tri" << endl;
				        cout << "4.Tim tong trong so lon nhat trong 2 robot A or B" << endl;
				        cout << "-------------------------------------------------------" << endl;
		                cout << "Chon chuc nang: ";
                        cin >> p3_2;
                        if (p3_2==1) {
                            cout << "Ban chon chuc nang 1"<<endl;
							int selectp3_2;
							cout<<"Tu nhap (p1): "<<endl;
							cout<<"May nhap (p2): "<<endl;
							cin>>selectp3_2;
							while(true){
							if(selectp3_2==1){
							cout<<"Ban chon tu nhap : "<<endl;
                        	cout << "Nhap so hang: ";
						    cin >> m.row;
						    cout << "Nhap so cot: ";
						    cin >> m.col;
						    m.a = new int*[m.row];
						    for (int i = 0; i < m.row; i++)
						    {
						        m.a[i] = new int[m.col];
						    }
						
						    inputl3(m); 
						    output(m, outfile);
							cout<<endl<<"Ma tran: "<<m.row<<"x"<<m.col<<endl;
							} if(selectp3_2==2)
							{
								cout<<"Ban chon may nhap:"<<endl;
								srand(time(0));
								m.row = rand() % 6+5;
								m.col = rand() % 4+7;
							m.a = new int*[m.row];
						    for (int i = 0; i < m.row; i++)
						    {
						        m.a[i] = new int[m.col];
						    }
						
						    inputl3(m); 
						    output(m, outfile);
							cout<<endl<<"Ma tran: "<<m.row<<"x"<<m.col<<endl;
							}
							cout << "Bam 'x' de thoat : ";
                			cin >> exitkey;
                			if (exitkey == 'x') {
                				
                    			cout << "Da thoat  "<<endl;
                    			break;
                				}
							}
						    cout << endl;
						} else if(p3_2==2){
							cout<<"Ban chon chuc nang 2"<<endl;
							cout << "2.Tim quang duong cua robot trong ma tran" << endl;
				            robot r;
				            r.kq = new int[m.row * m.col];
				            outfile << "Ket qua : " << endl;
				            robotpath(m, r, outfile);
				            outfile << endl;
				            delete[] r.kq;
				            cout << endl;
				    	} else if(p3_2==3){
				    		cout<<"Ban chon chuc nang 3"<<endl;
			    			cout << "3.Tim so vi tri giao nhau cua 2 robot khi dat o 2 vi tri" << endl;
				            robot r1, r2;
				            r1.kq = new int[m.row * m.col];
				            r2.kq = new int[m.row * m.col];
				            outfile << "Ket qua :" << endl;
				            intersect(m, r1, r2, outfile);
				            outfile << endl;
				            delete[] r1.kq, r2.kq;
				            cout << endl;
						} else if(p3_2==4){
							cout<<"Ban chon chuc nang 4"<<endl;
							cout << "4.Tim tong trong so lon nhat trong 2 robot A or B" << endl;
				            int ax, ay, bx, by;
				            cout << "Nhap vi tri cua Robot A: ";
				            cin >> ax >> ay;
				           	srand(time(0));
							bx = rand() % m.row;
							by = rand() % m.col;
							cout<<"Vi tri cua Robot B: ";
							cout<<bx<<" "<<by<<endl;
				            outfile << "Ket qua :" << endl;
				            whowin(m, ax, ay, bx, by, outfile);
				            cout << endl;
								
                    	} else {
                            cout << "Khong co chuc nang nay" << endl;
                        }
                            cout << "Bam 'x' de thoat muc 3 : ";
                			cin >> exitkey;
                			if (exitkey == 'x') {
                				
                    			cout << "Da thoat muc " <<p3_2<< endl;
                    			break;
                				}
                			}break;
                    default:
                        cout<< "Khong co chuc nang nay"<<endl; 
                }
                cout<< "Bam 'x' de thoat che do : "; 
                cin>>exitkey; 
                if(exitkey=='x'){
                    cout<< "Da thoat che do "<<mode<<endl;
					break; 
                }
            }
            break;
            case 3:{
                cout << "Ban dang trong che do 3" << endl;
                int p3;
				system("notepad huongdangame.txt");
                cout << "Bam 'x' de thoat che do: ";
                cin >> exitkey;
                if (exitkey == 'x') {
                    cout << "Da thoat che do" <<mode<< endl;
                }
                break;}
            default:
                cout << "Khong co che do nay" << endl;
        }

		time_t now = time(0);
		char* dt = ctime(&now);
		outfile<<endl<<"Ban chon che do "<<mode<<" luc: "<<dt<<endl;
        cout << "Ban co muon tiep tuc choi: (y/n): ";
        char continueplay;
        cin >> continueplay;
        if (continueplay == 'n') {
            exitgame = 1;
            outfile.close();
            
			for (int i = 0; i < m.row; i++) {
				delete[] m.a[i];
			}
			delete[] m.a;
			system("notepad lichsugame.txt");
        }

    }

    return 0; 
}
