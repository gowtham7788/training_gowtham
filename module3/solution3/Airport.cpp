#include "Airport.h"

Airport::Airport()
{

}

Airport::~Airport()
{
}

string Airport::genarateAirId()
{
	string aid;
	Airplane airobj;
	int random_number;
	time_t end_time;
	random_number = rand() % 60;
	end_time = time(NULL) + random_number;
	while (1)
	{
		if (time(NULL) > end_time)
		{
			aid = "AID" + to_string(id);
			id++;
			break;
		}
	}
	return aid;
}

void Airport::generateRequest()
{
	Airplane airobj;
	string req;
	string rid;
	string aero_id;
	Request newRequest;
	time_t t;
	aero_id = genarateAirId();
	airobj.setAirplaneId(aero_id);
	airways.push_back(airobj);
	rid = airobj.generateRequestId();
	req = airobj.generateRequestType(aero_id);
	newRequest.setAeroId(aero_id);
	newRequest.setRequestId(rid);
	newRequest.setRequestType(req);
	t = time(NULL);
	newRequest.setInTime(t);
	if (req == "landing")
	{
		landingQueue.push(newRequest);
	}
	else
	{
		takeoffQueue.push(newRequest);
	}		
}

void Airport::checkRunway1(time_t total_time)
{
	
	int start_time;
	time_t end_time;
	struct tm info;
	Request popedRequest;
	if (runway1.getStatus() == 0)
	{
		
		
		if (!landingQueue.isEmpty())
		{
		runway1.setStatus(1);	
			popedRequest=landingQueue.pop();
			start_time = popedRequest.getInTime();
			end_time = time(NULL);
			landing_time = landing_time + (end_time - start_time);
			localtime_s(&info, &end_time);
			cout << "\nRequest id " << popedRequest.getReqId() << "started landing on runway 1 at " << info.tm_hour << " : " << info.tm_min << " : " << info.tm_sec<<endl;
			landed.push_back(popedRequest);

			if ((total_time - end_time) < time_taken)
			{
				time_taken = (total_time - end_time);
			}
			this_thread::sleep_for(chrono::seconds(time_taken));
			end_time = time(NULL);
			localtime_s(&info, &end_time);
			cout << "\nRequest id " << popedRequest.getReqId() << "finished landing on runway 1 at " << info.tm_hour << " : " << info.tm_min << " : " << info.tm_sec << endl;
		runway1.setStatus(0);
		}
		else
		{
			
			if (!takeoffQueue.isEmpty())
			{
				runway1.setStatus(1);
				popedRequest = takeoffQueue.pop();
				start_time = popedRequest.getInTime();
				end_time = time(NULL);
				localtime_s(&info, &end_time);
				takeoff_time = takeoff_time + (end_time - start_time);
				cout << "\nRequest id " << popedRequest.getReqId() << "started takeoff on runway 1 at " << info.tm_hour << " : " << info.tm_min << " : " << info.tm_sec << endl;
				tookoff.push_back(popedRequest);
				if ((total_time - end_time) < time_taken)
				{
					time_taken = (total_time - end_time);
				}
				this_thread::sleep_for(chrono::seconds(time_taken));
				end_time = time(NULL);
				localtime_s(&info, &end_time);
				cout << "\nRequest id " << popedRequest.getReqId() << "finished landing on runway 1 at " << info.tm_hour << " : " << info.tm_min << " : " << info.tm_sec << endl;
			runway1.setStatus(0);
			}
		}
		
	}
}

void Airport::checkRunway2(time_t total_time)
{
	
	int start_time;
	time_t end_time;
	Request popedRequest;
	struct tm info;
	if (runway2.getStatus() == 0)
	{
		
		
		if (!landingQueue.isEmpty())
		{
		runway2.setStatus(1);
			popedrequest = landingQueue.pop();
			start_time = popedRequest.getInTime();
			end_time = time(NULL);
			landing_time = landing_time + (end_time - start_time);
			localtime_s(&info, &end_time);
			cout << "\nRequest id " << popedRequest.getReqId() << " started landing on runway 2 at " << info.tm_hour << " : " << info.tm_min << " : " << info.tm_sec << endl;
			landed.push_back(popedRequest);
			if ((total_time - end_time) < time_taken)
			{
				time_taken = (total_time - end_time);
			}
			this_thread::sleep_for(chrono::seconds(time_taken));
			end_time = time(NULL);
			localtime_s(&info, &end_time);
			cout << "\nRequest id " << popedRequest.getReqId() << "finished landing on runway 2 at " << info.tm_hour << " : " << info.tm_min << " : " << info.tm_sec << endl;
		runway2.setStatus(0);
		}
		else
		{
			
			if (!takeoffQueue.isEmpty())
			{
				runway2.setStatus(1);
				popedRequest = takeoffQueue.pop();
				start_time = popedRequest.getInTime();
				end_time = time(NULL);
				localtime_s(&info, &end_time);
				takeoff_time = takeoff_time + (end_time - start_time);
				cout << "\nRequest id " << popedRequest.getReqId() << "started takeoff on runway 1 at " << info.tm_hour << " : " << info.tm_min << " : " << info.tm_sec << endl;
				tookoff.push_back(popedRequest);
				if ((total_time - end_time) < time_taken)
				{
					time_taken = (total_time - end_time);
				}
				this_thread::sleep_for(chrono::seconds(time_taken));
				end_time = time(NULL);
				localtime_s(&info, &end_time);
				cout << "\nRequest id " << popedrequest.getReqId() << "finished landing on runway 1 at " << info.tm_hour << " : " << info.tm_min << " : " << info.tm_sec << endl;
			runway2.setStatus(0);
			}
		}
		
	}
}

void Airport::callGenerateRequest(time_t total_time)
{
	while (1)
	{
		if (time(NULL) < total_time)
		{
			generateRequest();
		}
		else
		{
		float average;
				int waiting_time;		
			
			cout << "\nLanding count " << landingQueue.getCount();
			cout << "\nTakeoff count " << takeoffQueue.getCount();
			cout << "\nLanding Queue\n";
			waiting_time=landingQueue.displayQueue();
			landing_time+=waiting_time;
			cout << "\ntotal landing wait time  " << landing_time;     
			average = (float)landing_time / (landingQueue.getCount()+landingQueue.calculateQueueSize());  
			cout << "\nAverage landing time " << average;
			
			
			cout << "\nTakeoff  Queue\n";
			waiting_time=takeoffQueue.displayQueue();
			takeoff_time+=waiting_time;
			
			cout << "\ntotal takeoff wait time " << takeoff_time;
			average = (float)takeoff_time / (takeoffQueue.getCount()+takeoffQueue.calculateQueueSize());
			cout << "\nAverage takeoff time " << average;
			break;
		}
	}
}

void Airport::callCheckRunway1(time_t total_time)
{
	while (1)
	{
		if (time(NULL) < total_time)
		{
			checkRunway1(total_time);
		}
		else
		{
			break;
		}
	}
}

void Airport::callCheckRunway2(time_t total_time)
{
	while (1)
	{
		if (time(NULL) < total_time)
		{
			checkRunway2(total_time);
		}
		else
		{
			break;
		}
	}
}
