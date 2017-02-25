#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
class sortobject{
	public:
	  int index;
	  int value;
	  sortobject(){
	    index=-1;
	    value=-1;
	  }
	  sortobject(int i, int v){
	    index=i;
	    value=v;
	  }
};
int sortAlgoAsc(const void* va, const void* vb){
  const sortobject* a;
  a=(const sortobject*) va;
  const sortobject* b;
  b= (const sortobject*) vb;
	if(a->value > 0 && b->value > 0){
		if(a->value > b->value) return 1;
	  else if(a->value < b->value) return -1;
	  else{
			if(a->index > b->index) return 1;
			else if(a->index < b->index) return -1;
			else {return 0;} //just in case
		}
	}
	else{
		if(a->value < 0 && b->value < 0) return 0;
		else if(a->value < 0) return 1;
		else if(b->value < 0) return -1;
	}
}
int sortAlgoDes(const void* va, const void* vb){
  const sortobject* a;
  a=(const sortobject*) va;
  const sortobject* b;
  b= (const sortobject*) vb;
  if(a->value > b->value) return -1;
  else if(a->value < b->value) return 1;
	else{
		if(a->index > b->index) return -1;
		else if(a->index < b->index) return 1;
		else {return 0;} //just in case
	}
}

sortobject* sortObject(int* array, int size, int order){
  int i=0;

  sortobject* sorted = new sortobject[size];
  for(i=0; i<size; i++){
    sortobject temp(i, array[i]);
    sorted[i]=temp;
  }
	if(order==0){
		qsort(sorted, size, sizeof(sortobject), sortAlgoDes);
	}
	else if(order==1){
		qsort(sorted, size, sizeof(sortobject), sortAlgoAsc);
	}

	return sorted;
}

int main() {
	cout<<"Started"<<endl;
	cout<<"Checkpoint 0: Creating Streams"<<endl;

	int i, j, k; //USED FOR FOR LOOP PARAMETERS!
	int numberVideos;
	int numberEndpoints;
	int numberRequestdescription;
	int numberCaches;
	int sizeCaches;


	ifstream filestream;
	filestream.open("C:\\Users\\USERNAME\\Desktop\\me_at_the_zoo.in");

	ofstream logstream;
	logstream.open("C:\\Users\\USERNAME\\Desktop\\log.txt");

	ofstream outputstream;
	outputstream.open("C:\\Users\\USERNAME\\Desktop\\me_at_the_zoo.txt");



	cout<<"Checkpoint 1: Taking input"<<endl;

	filestream >> numberVideos;
	filestream >> numberEndpoints;
	filestream >> numberRequestdescription;
	filestream >> numberCaches;
	filestream >> sizeCaches;

	logstream << "Number of videos: " << numberVideos << endl;
	logstream << "Number of endpoints: " << numberEndpoints << endl;
	logstream << "Number of request descriptions: " << numberRequestdescription << endl;
	logstream << "Number of cache servers: " << numberCaches << endl;
	logstream << "Size of each cache server: " << sizeCaches << endl;
	logstream << endl;

	int* sizeVideos = new int[numberVideos];

	for (i = 0; i < numberVideos; i++) {
		filestream >> sizeVideos[i];
		logstream << "Size of video" << i << ": " << sizeVideos[i] << endl;
	}

	int* endpointsVSdatacenterlatency = new int[numberEndpoints];
	int* numberConnectedCachesforEndpoints = new int[numberEndpoints];
	int** latenciesBetweenEndpointsandCaches = new int*[numberEndpoints];
	for (i = 0; i < numberEndpoints; i++) {
		latenciesBetweenEndpointsandCaches[i] = new int[numberCaches];
	}
	logstream<<endl;

	for (i = 0; i<numberEndpoints; i++) {
		filestream >> endpointsVSdatacenterlatency[i];
		logstream << "Latency of Endpoint" << i << " to data center: " << endpointsVSdatacenterlatency[i] << endl;
		filestream >> numberConnectedCachesforEndpoints[i];
		logstream << "Number of caches Endpoint" << i << ": " << numberConnectedCachesforEndpoints[i] << endl;
		for (j = 0; j<numberConnectedCachesforEndpoints[i]; j++) { //Initialize with no-connections
			latenciesBetweenEndpointsandCaches[i][j] = 999999;
			//not connected = 999999 ms Latency
		}
		for (j = 0; j<numberConnectedCachesforEndpoints[i]; j++) {
			int cacheId;
			filestream >> cacheId;
			filestream >> latenciesBetweenEndpointsandCaches[i][cacheId];
			logstream << "Latency between Endpoint" << i << " to CacheServer" << cacheId << ": " << latenciesBetweenEndpointsandCaches[i][cacheId] << endl;
		}
		logstream<<endl;
	}

	int** numberRequestsfromEndpointsforVideos = new int*[numberEndpoints];
	for (i = 0; i < numberVideos; i++){
		numberRequestsfromEndpointsforVideos[i] = new int[numberVideos];
	}

	for (i = 0; i<numberEndpoints; i++) { //Initialize array with Zeros
		for (j = 0; j<numberVideos; j++) {
			numberRequestsfromEndpointsforVideos[i][j] = 0;
		}
	}

	for (i = 0; i<numberRequestdescription; i++) {
		int videoId;
		int endpointId;
		int numberRequests;
		filestream >> videoId;
		filestream >> endpointId;
		filestream >> numberRequests;
		numberRequestsfromEndpointsforVideos[endpointId][videoId] = numberRequests;
		logstream << "Endpoint[" << endpointId << "] requested Video[" << videoId << "] " << numberRequests << " times" << endl;
	}
	logstream<<endl;




	cout<<"Checkpoint 2: Processing data"<<endl;

  int* totalRequestsforVideos = new int[numberVideos];
  for(i=0; i<numberVideos; i++){
    totalRequestsforVideos[i]=0; // Initialize with zeros
    for(j=0; j<numberEndpoints; j++){
      totalRequestsforVideos[i]+=numberRequestsfromEndpointsforVideos[j][i];
    }
		if(totalRequestsforVideos[i]>0){
			logstream<<"Total number of requests for Video"<<i<<": "<<totalRequestsforVideos[i]<<endl;
		}
  }
	logstream<<endl;

  sortobject* SORTEDtotalRequestsforVideos = sortObject(totalRequestsforVideos, numberVideos, 0);


	for(i=0;i<numberVideos;i++){

		logstream<<"Video["<<SORTEDtotalRequestsforVideos[i].index<<"] has "<<SORTEDtotalRequestsforVideos[i].value<<" requests"<<endl;
  }
	logstream<<endl;



	cout<<"Checkpoint 3: Preparing for the algorithm"<<endl;

	int** cachesHoldingVideos = new int*[numberCaches];
	for (i = 0; i < numberCaches; i++){
		cachesHoldingVideos[i] = new int[numberVideos];
	}

	for(i=0; i<numberCaches; i++){ //Initialize with zeros
		for(j=0; j<numberVideos; j++){
			cachesHoldingVideos[i][j]=0; //0 is false, 1 is true
		}
	}


	int* occupiedSizeofCache = new int[numberCaches];


	for(i=0; i<numberCaches; i++){ //Initialize with zeros
		occupiedSizeofCache[i]=0;
	}


	int** foreachVideoCacheGrades = new int*[numberVideos];
	for(i=0; i<numberVideos; i++){
		foreachVideoCacheGrades[i] = new int[numberCaches];
	}


	sortobject** SORTEDforeachVideoCacheGrades = new sortobject*[numberVideos];





	cout<<"Checkpoint 4: Algorithm running"<<endl;
	logstream<<endl<<"Algorithm Started"<<endl;
	logstream<<endl<<"Cache grading started"<<endl;

	for(j=0; j<numberVideos; j++){
		logstream<<endl<<"Processing Case: Video[" << SORTEDtotalRequestsforVideos[j].index <<"]"<<endl;

		//Grading caches here
		for(i=0; i<numberEndpoints; i++){
			for(k=0; k<numberCaches; k++){
				if(numberRequestsfromEndpointsforVideos[i][SORTEDtotalRequestsforVideos[j].index]>0){
					foreachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k]+=latenciesBetweenEndpointsandCaches[i][k]*numberRequestsfromEndpointsforVideos[i][SORTEDtotalRequestsforVideos[j].index];
				}
			}
		}
		for(k=0; k<numberCaches; k++){
			logstream<<"For Video["<<SORTEDtotalRequestsforVideos[j].index<<"], grade of Cache["<<k<<"]: "<<foreachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k]<<endl;
		}
		logstream<<endl;


		SORTEDforeachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index] = sortObject(foreachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index], numberCaches, 1);


		logstream<<"For Video["<<SORTEDtotalRequestsforVideos[j].index<<"]"<<endl;
		for(k=0; k<numberCaches; k++){
			logstream<<"Cache["<<SORTEDforeachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k].index<<"] has "<<SORTEDforeachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k].value<<" points"<<endl;
		}
		logstream<<endl;
	}



	//Registration here
	logstream<<endl<<"Video registration started"<<endl;
	for(i=0; i<numberCaches; i++){
		//Repeat number of caches times, because i.e the best video may be registered to all of them
		for(j=0; j<numberVideos; j++){
			for(k=0; k<numberCaches; k++){
				if(occupiedSizeofCache[SORTEDforeachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k].index]+sizeVideos[SORTEDtotalRequestsforVideos[j].index]<=sizeCaches
						&& cachesHoldingVideos[SORTEDforeachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k].index][SORTEDtotalRequestsforVideos[j].index]==0
						&& 	SORTEDtotalRequestsforVideos[j].value>0){
				// if size in the cache is enough &&
				// if the video is not already registered to that cache &&
				// if the video is requested at least once

					logstream<<"Size of Video["<<SORTEDtotalRequestsforVideos[j].index<<"]: "<<sizeVideos[SORTEDtotalRequestsforVideos[j].index]<<endl;
					logstream<<"Occupied size of Cache["<< SORTEDforeachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k].index << "]: "<< occupiedSizeofCache[SORTEDforeachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k].index]<<"/"<<sizeCaches<<endl;
					cachesHoldingVideos[SORTEDforeachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k].index][SORTEDtotalRequestsforVideos[j].index]=1;
					logstream<<"Video["<<SORTEDtotalRequestsforVideos[j].index<<"] is registered to Cache["<< SORTEDforeachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k].index<<"]"<<endl;
					occupiedSizeofCache[SORTEDforeachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k].index]+=sizeVideos[SORTEDtotalRequestsforVideos[j].index];
					logstream<<"New size of Cache["<< SORTEDforeachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k].index<<"]: "<< occupiedSizeofCache[SORTEDforeachVideoCacheGrades[SORTEDtotalRequestsforVideos[j].index][k].index]<<"/"<<sizeCaches<<endl;
					logstream<<endl;
					break; //the video is registered to this cache, move to the next video, not the next cache
				}
			}
		}
	}





	cout<<"Checkpoint 5: Writing output data"<<endl;

	int isCacheUsed=0;
	int cachesUsed=0;
	for(i=0; i<numberCaches; i++){
		isCacheUsed=0;
		for(j=0; j<numberVideos; j++){
			if(cachesHoldingVideos[i][j]==1){
				isCacheUsed=1;
				logstream<<"Cache["<<i<<"] is used"<<endl;
			}
		}
		if(isCacheUsed==1){
			cachesUsed++;
		}
	}

	logstream<<"In total "<<cachesUsed<<" caches used"<<endl;
	outputstream<<cachesUsed<<endl;

	for(i=0; i<numberCaches; i++){
		outputstream<<i<<" ";
		logstream<<"Cache["<<i<<"] is loaded with ";
		for(j=0; j<numberVideos; j++){
			if(cachesHoldingVideos[i][j]==1){
				logstream<<"Video["<<j<<"]";
				outputstream<<j;
				if(j<numberVideos-1){ //if not the last element, put a space
					logstream<<" ";
					outputstream<<" ";
				}
			}
		}
		outputstream<<endl;
		logstream<<endl;
	}

	logstream<<endl<<"Finished"<<endl;
	cout<<endl<<"Finished!"<<endl;
	return 0;




}
