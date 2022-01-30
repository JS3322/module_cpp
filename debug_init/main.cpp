#include<omp.h>
#include<time.h>
#include<iostream>
#include<algorithm>
#include"DS_timer.h"
#define SIZE (1024*1024*16)		//1073741824 //1024^3 //8GB 메모리는 512*1024*1024를 권장
#define THREAD 8				//스레드 개수

// ----- 변수 선언 ----- //
int RANGE;
float* rand_num = new float[SIZE];	//0~RANGE 랜덤 수
float** num;	//정렬할 배열
int* size;		//각 범위 개수 저장 후 동적할당에 사용
int* count;		//나누어 저장시 카운트로 사용

// ----- 커서 이동 ----- //
inline void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
// ----- 진행률 표시 ----- //
inline void readPercentage(int now, int max, int line=0) {
	static int temp = -1;
	if (temp != (int)((100.0 / max) * now)) {
		temp = (int)((100.0 / max) * now);
		gotoxy(18, line);
		printf("%3d%%]", temp+1-line);
	}
}
// ----- 각 인덱스의 배열 동적할당 ----- //
void makeMemory() {
	//size배열을 최대값만큼 동적할당하고 각 구간의 갯수 카운트
	size = new int[RANGE];
	count = new int[RANGE];
	num = new float*[RANGE];
	memset(size, 0, RANGE * sizeof(int));
	memset(count, 0, RANGE * sizeof(int));
	printf("\n범위 : 0 ~ %d\n", RANGE);
	for (int i = 0; i < SIZE; i++)
		size[(int)rand_num[i]]++;
	//0~RANGE의 float 개수만큼 동적할당
	for (int i = 0; i < RANGE; i++)
		num[i] = new float[size[i]];
}
// ----- 0~range 범위의 랜덤 수 생성 ----- //
void random(int range){
	#pragma omp parallel for num_threads(THREAD)
	for (int i = 0; i < SIZE; i++) {
		rand_num[i] = (rand()*rand()) % (range * 10000) / (float)10000;
		if(omp_get_thread_num()==0) readPercentage(i*THREAD, SIZE);
	}
	RANGE = range;
}
// ----- 파일 읽기 ----- //
void fileRead() {
	FILE *f;
	if (!(f = fopen("input.txt", "r")))
		printf("파일이 없습니다.\n");
	//파일을 읽으면서 최댓값 찾기
	for (int i = 0; i < SIZE; i++) {
		fscanf(f, "%f ", &rand_num[i]);
		if (RANGE < rand_num[i]) RANGE = rand_num[i];
		readPercentage(i, SIZE);
	}
	fclose(f);
	RANGE++;
}
// ----- 파일 쓰기 ----- //
void fileWrite(char* filename, int from = 0, int to = RANGE) {
	FILE *f;
	if (!(f = fopen(filename, "w")))
		printf("파일을 쓸 수 없습니다.\n");

	for (int i = from; i < to; i++)
		for (int j = 0; j < size[i]; j++)
			fprintf(f, "%f ", num[i][j]);
	fclose(f);
}

void main(){
	// ----- 타이머 선언 ----- //
	DS_timer timer(2);
	timer.initTimers();
	srand(time(NULL));

	// ----- 파일 읽기 ----- //
	printf("파일을 읽는 중...[   %%]");
	//fileRead();			//파일에서 랜덤수를 받아옴
	random(rand()%991+10);	//랜덤으로 숫자 생성(10~1000)
	makeMemory();
	int from, to;
	printf("파일을 모두 읽어왔습니다.\n");
	printf("검색 범위를 입력하세요.\n");
	printf("예시) 2부터 6까지 = 2 6 : ");
	scanf("%d %d", &from, &to);

	system("cls");
	printf("값 정렬하는 중1..[   %%]");
	timer.onTimer(0);
	//0~RANGE 배열에 각각 나누어 저장 - Serial로 처리
	for (int i = 0; i < SIZE; i++){
		num[(int)rand_num[i]][count[(int)rand_num[i]]++] = rand_num[i];
		readPercentage(i, SIZE);
	}

	// ----- 0~RANGE 배열 각각 정렬 ----- //
	printf("\n값 정렬하는 중2..[   %%]");
	// ----- Serial 방식 ----- //
	/*
	for (int i = 0; i < RANGE; i ++) {
		std::sort(num[i], num[i] + size[i]);
		readPercentage(i+1, RANGE, 1);
	}
	*/
	
	// ----- OpenMP 방식 ----- //
	
	int now = 0;
	#pragma omp parallel for schedule(guided, 1) num_threads(THREAD) 
	for (int i = 0; i < RANGE; i++) {
		std::sort(num[i], num[i] + size[i]);
		#pragma omp critical
		readPercentage(++now, RANGE, 1);
	}
	

	timer.offTimer(0);
	timer.printTimer();

	// ----- 파일 저장 ----- //
	int total = 0;
	timer.onTimer(1);
	for (int i = from; i < to; i++)
		total += size[i];
	timer.offTimer(1);
	printf("검색된 데이터 수 : %d개\n", total);
	fileWrite("sort.txt");
	fileWrite("search.txt", from, to);
}