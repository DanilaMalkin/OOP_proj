#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <cassert>

using namespace std;

class Station {
public:
    // Конструктор по умолчанию
    Station() {
        name = "NONAME";
        town = "NONAME";
        stopTime = 10;
    }

    // Конструктор с параметрами
    Station(const string& valueName, const string& valueTown) {
        name = valueName;
        town = valueTown;
        stopTime = 10;
    }

    // Конструктор копирования
    Station(const Station& other) {
        name = other.name;
        town = other.town;
        stopTime = other.stopTime;
        trains = other.trains;
    }

    // Деструктор
    ~Station() {}

    // Методы получения значений
    string getName() const {
        return name;
    }

    string getTown() const {
        return town;
    }

    int getStopTime() const {
        return stopTime;
    }

    vector<int> getTrain() const {
        return trains;
    }

    // Метод установки нового поезда
    void setNewTrain(const vector<int>& newTrain) {
        trains = newTrain;
    }

    // Метод установки нового имени
    void setName(const string& newName) {
        name = newName;
    }

    // Метод установки нового города
    void setTown(const string& newTown) {
        town = newTown;
    }

    // Метод установки нового времени остановки
    void setStopTime(int newStopTime) {
        stopTime = newStopTime;
    }

private:
    string name;
    string town;
    int stopTime;
    vector<int> trains;
};


class Train {
public:
    // Конструктор по умолчанию с установкой значений
    
    Train(int newNumber, int newSpeed, int newSize, int newStartTime) {
            number = newNumber;
            speed = newSpeed;
            size = newSize;
            startTime = newStartTime;
    }
    
    Train() {
        number  = 0;
        speed = 0;
        size = 0;
        startTime = 0;
    }

    Train(const Train& other){
        number = other.number;
        speed = other.speed;
        size = other.size;
        startTime = other.startTime;
        route = other.route;
    }
        


    ~Train() {}

  
    int getNumber() const {
        return number;
    }

    int getSpeed() const {
        return speed;
    }

    int getSize() const {
        return size;
    }

    int getStartTime() const {
        return startTime;
    }

    vector<pair<Station, int>> getRoute() const {
        return route;
    }


    void setNumber(int newNumber) {
        number = newNumber;
    }

    void setSpeed(int newSpeed) {
        speed = newSpeed;
    }

    void setSize(int newSize) {
        size = newSize;
    }

    void setStartTime(int newStartTime) {
        startTime = newStartTime;
    }

    void setRoute(const vector<pair<Station, int>>& newRoute) {
        route = newRoute;
    }

private:
    int number;
    int speed;
    int size;
    int startTime;
    vector<pair<Station, int>> route;
};



class ElectricTrain : public Train {
public:
    ElectricTrain() : Train(){
        freeSits = 0;
        passengersNumber = 0;
    }
    
   
    ElectricTrain(int newNumber, int newSpeed, int newSize, int newStartTime, int valueFreeSits, int valuePassengersNumber)
        : Train(newNumber, newSpeed, newSize, newStartTime) {
        freeSits = valueFreeSits;
        passengersNumber = valuePassengersNumber;
    }


   
    ElectricTrain(const ElectricTrain& other) : Train(other){
        freeSits = other.freeSits;
        passengersNumber = other.passengersNumber;
    }

    
    

    // Уникальный деструктор для ElectricTrain
    ~ElectricTrain() {
    
    }

    int getFreeSits() const {
        return freeSits;
    }

    int getPassengersNumber() const {
        return passengersNumber;
    }

    void setFreeSits(int newFreeSits) {
        freeSits = newFreeSits;
    }

    void setPassengersNumber(int newPassengersNumber) {
        passengersNumber = newPassengersNumber;
    }

private:
    int freeSits;
    int passengersNumber;
};

class CargoTrain : public Train {
public:
    CargoTrain() : Train() {
        weightCargo = 0;
    }
    CargoTrain(int newNumber, int newSpeed, int newSize, int newStartTime, int valueWeightCargo)
        : Train(newNumber, newSpeed, newSize, newStartTime) {
        weightCargo = valueWeightCargo;
    }

   
    CargoTrain(const CargoTrain& other) : Train(other){
        weightCargo = other.weightCargo;
    
    }

    // Уникальный деструктор для CargoTrain
    ~CargoTrain() {
     
    }

    int getWeightCargo() const {
        return weightCargo;
    }

    void setWeightCargo(int newWeightCargo) {
        weightCargo = newWeightCargo;
    }

private:
    int weightCargo;
};

class PassengerTrain : public Train {
public:
    
    PassengerTrain() : Train(){
        freeSits = 0;
        passengersNumber = 0;
    }
    
    PassengerTrain(int newNumber, int newSpeed, int newSize, int newStartTime, int valueFreeSits, int valuePassengersNumber)
        : Train(newNumber, newSpeed, newSize, newStartTime) {
        freeSits = valueFreeSits;
        passengersNumber = valuePassengersNumber;
    }

   
    PassengerTrain(const PassengerTrain& other) : Train(other){
        freeSits = other.freeSits;
        passengersNumber = other.passengersNumber;
    }


    ~PassengerTrain() {
        
    }

    int getPassengersNumber() const {
        return passengersNumber;
    }

    int getFreeSits() const {
        return freeSits;
    }

    void setPassengersNumber(int newPassengersNumber) {
        passengersNumber = newPassengersNumber;
    }

    void setFreeSits(int newFreeSits) {
        freeSits = newFreeSits;
    }

private:
    int passengersNumber;
    int freeSits;
};
class TrainSchedule;

class RouteGraph {
private:
    vector<pair<Station, pair<Station, int>>> edges;
    vector<pair<Station, pair<Station, Train>>> schedule;
    
public:
    int timer(const Train& trtr, const Station& source, const Station& destination) const {
        int distance = getWeight(source, destination);
        //cout << "вес" << distance << endl;
        int speed = trtr.getSpeed();
        //cout << "скорость" << speed << endl;
        return distance / speed;
    }
    
    bool isRouteFree(const Station& source, const Station& destination, const Train& train) {
        for (const auto& entry : schedule) {
            const Station& entrySource = entry.first;
            const Station& entryDestination = entry.second.first;
            const Train& entryTrain = entry.second.second;

            // Проверка, свободен ли путь для данного поезда
            if (entrySource.getName() == source.getName() && entryDestination.getName() == destination.getName()) {
                cout << "Поезд " << train.getNumber() << ": " << source.getName() << " -> " << destination.getName() << endl;

                // Получение маршрута текущего поезда и поезда из расписания
                const vector<pair<Station, int>>& entryRoute = entryTrain.getRoute();
                const vector<pair<Station, int>>& route = train.getRoute();

                // Проверка по времени
                for (const auto& entryStep : entryRoute) {
                    for (const auto& trainStep : route) {
                        if (entryStep.first.getName() == trainStep.first.getName()) {
                            // Проверка временных участков
                            int entryArrivalTime = timer(entryTrain, entrySource, entryDestination) + entryStep.second;
                            int entryDepartureTime = entryArrivalTime ;
                            int trainArrivalTime = timer(train, source, destination) + trainStep.second;
                            int trainDepartureTime = trainArrivalTime ;

                            // Проверка пересечения временных участков
                            if ((entryArrivalTime >= trainArrivalTime && entryArrivalTime <= trainDepartureTime) ||
                                (entryDepartureTime >= trainArrivalTime && entryDepartureTime <= trainDepartureTime) ||
                                (trainArrivalTime >= entryArrivalTime && trainArrivalTime <= entryDepartureTime) ||
                                (trainDepartureTime >= entryArrivalTime && trainDepartureTime <= entryDepartureTime) ||
                                (entryArrivalTime == trainArrivalTime) || (trainDepartureTime == entryDepartureTime)) {
                                cout << "Временные участки пересекаются, путь не свободен" << endl;
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    void addSchedule(const Train& train) {
        vector<pair<Station, int>> trainRoute = train.getRoute();
        for (size_t i = 0; i < trainRoute.size() - 1; ++i) {
            const Station& source = trainRoute[i].first;
            const Station& destination = trainRoute[i + 1].first;
            
            if (!isRouteFree(source, destination, train)) {
                cout << "Error: Train " << train.getNumber() << " has an invalid route in the graph." << endl;
                return;
            }
        }
        
        for (size_t i = 0; i < trainRoute.size() - 1; ++i) {
            const Station& source = trainRoute[i].first;
            const Station& destination = trainRoute[i + 1].first;
            schedule.push_back({source, {destination, train}});
        }
        
        cout << "Train " << train.getNumber() << " has been added to the schedule." << endl;
    }
    
    void addPath(const Station& source, const Station& destination, int weight) {
        edges.push_back({source, {destination, weight}});
    }
    
    int getWeight(const Station& source, const Station& destination) const {
        for (const auto& edge : edges) {
            if (edge.first.getName() == source.getName() &&
                edge.second.first.getName() == destination.getName()) {
                return edge.second.second;
            }
        }
        return -1;
    }


   /* bool hasPath(const vector<Station>& route, int trainNumber) const {
        for (size_t i = 0; i < route.size() - 1; ++i) {
            const Station& source = route[i];
            const Station& destination = route[i + 1];
            int currentTime = source.getStopTime();  // Время начала движения на станции

            bool pathExists = false;
            for (const auto& edge : edges) {
                if (edge.first.getName() == source.getName() &&
                    edge.second.first.getName() == destination.getName()) {

                    pathExists = true;
                    break;
                }
            }

            if (!pathExists) {
                return false;
            }
        }

        return true;
    }*/
};


int main() {
 
    Station stationA("A", "Moscow");
    assert(stationA.getName() == "A");
    assert(stationA.getTown() == "Moscow");
    assert(stationA.getStopTime() == 10);
    
    Station stationB("B", "St.Petersburg");
    assert(stationB.getName() == "B");
    assert(stationB.getTown() == "St.Petersburg");
    assert(stationB.getStopTime() == 10);
    
    Station stationC("C", "Perm");
    assert(stationC.getName() == "C");
    assert(stationC.getTown() == "Perm");
    assert(stationC.getStopTime() == 10);
    
    vector<int> trainRoute = {1, 2, 3};
    stationA.setNewTrain(trainRoute);
    assert(stationA.getTrain() == trainRoute);
    
    
    Train train1(1, 100, 200, 10);
    assert(train1.getNumber() == 1);
    assert(train1.getSpeed() == 100);
    assert(train1.getSize() == 200);
    assert(train1.getStartTime() == 10);
    
    Train train2(train1);
    assert(train2.getNumber() == 1);
    assert(train2.getSpeed() == 100);
    assert(train2.getSize() == 200);
    assert(train2.getStartTime() == 10);
    

    vector<pair<Station, int>> route = {{stationA, 10}, {stationB, 20}, {stationC, 30}};
    train1.setRoute(route);
    vector<pair<Station, int>> route3 = train1.getRoute();

    assert(route3[0].second == route[0].second);
    
    assert(route3[0].first.getName() == route[0].first.getName());
    assert(route3[0].first.getTown() == route[0].first.getTown());
    assert(route3[0].first.getStopTime() == route[0].first.getStopTime());

    
    ElectricTrain electricTrain(0,1,4,23,233,100);
    assert(electricTrain.getNumber() == 0);
    assert(electricTrain.getSpeed() == 1);
    assert(electricTrain.getSize() == 4);
    assert(electricTrain.getStartTime() == 23);
    assert(electricTrain.getFreeSits() == 233);
    assert(electricTrain.getPassengersNumber() == 100);
    
    // Test copying for ElectricTrain
    ElectricTrain electricTrainCopy(electricTrain);
    assert(electricTrainCopy.getNumber() == 0);
    assert(electricTrainCopy.getSpeed() == 1);
    assert(electricTrainCopy.getSize() == 4);
    assert(electricTrainCopy.getStartTime() == 23);
    assert(electricTrainCopy.getFreeSits() == 233);
    assert(electricTrainCopy.getPassengersNumber() == 100);


    ElectricTrain electricTrainDefault;
    assert(electricTrainDefault.getNumber() == 0);
    assert(electricTrainDefault.getFreeSits() == 0);
    assert(electricTrainDefault.getPassengersNumber() == 0);
    
    
    CargoTrain cargoTrain(2, 3, 5, 15, 500);
    assert(cargoTrain.getNumber() == 2);
    assert(cargoTrain.getSpeed() == 3);
    assert(cargoTrain.getSize() == 5);
    assert(cargoTrain.getStartTime() == 15);
    assert(cargoTrain.getWeightCargo() == 500);

    CargoTrain cargoTrainCopy(cargoTrain);
    assert(cargoTrainCopy.getNumber() == 2);
    assert(cargoTrainCopy.getSpeed() == 3);
    assert(cargoTrainCopy.getSize() == 5);
    assert(cargoTrainCopy.getStartTime() == 15);
    assert(cargoTrainCopy.getWeightCargo() == 500);

    CargoTrain cargoTrainDefault;
    assert(cargoTrainDefault.getNumber() == 0);
    assert(cargoTrainDefault.getWeightCargo() == 0);

    // Test copying for PassengerTrain
    PassengerTrain passengerTrain(0,1,4,23,233,100);
    assert(passengerTrain.getNumber() == 0);
    assert(passengerTrain.getSpeed() == 1);
    assert(passengerTrain.getSize() == 4);
    assert(passengerTrain.getPassengersNumber() == 100);
    assert(passengerTrain.getFreeSits() == 233);

    PassengerTrain passengerTrainCopy(passengerTrain);
    assert(passengerTrainCopy.getNumber() == 0);
    assert(passengerTrainCopy.getPassengersNumber() == 100);
    assert(passengerTrainCopy.getFreeSits() == 233);

    PassengerTrain passengerTrainDefault;
    assert(passengerTrainDefault.getNumber() == 0);
    assert(passengerTrainDefault.getFreeSits() == 0);
    assert(passengerTrainDefault.getPassengersNumber() == 0);
 

    
    return 0;
}
/*

    ElectricTrain electricTrainCopy(electricTrain);
    assert(electricTrainCopy.getNumber() == 0);
    assert(electricTrainCopy.getFreeSits() == 50);
    assert(electricTrainCopy.getPassengersNumber() == 100);

    // Test CargoTrain class
    CargoTrain cargoTrain;
    assert(cargoTrain.getNumber() == 0);
    assert(cargoTrain.getWeightCargo() == 0);

    CargoTrain cargoTrainCopy(cargoTrain);
    assert(cargoTrainCopy.getNumber() == 0);
    assert(cargoTrainCopy.getWeightCargo() == 0);

    // Test PassengerTrain class
    PassengerTrain passengerTrain(30, 80);
    assert(passengerTrain.getNumber() == 0);
    assert(passengerTrain.getPassengersNumber() == 80);
    assert(passengerTrain.getFreeSits() == 30);

    PassengerTrain passengerTrainCopy(passengerTrain);
    assert(passengerTrainCopy.getNumber() == 0);
    assert(passengerTrainCopy.getPassengersNumber() == 80);
    assert(passengerTrainCopy.getFreeSits() == 30);

    // Test RouteGraph class
    RouteGraph routeGraph;
    routeGraph.addPath(stationA, stationB, 10);
    routeGraph.addPath(stationB, stationC, 15);

    assert(routeGraph.getWeight(stationA, stationB) == 10);
    assert(routeGraph.getWeight(stationB, stationC) == 15);

    vector<pair<Station, int>> routeABC = {{stationA, 10}, {stationB, 20}, {stationC, 30}};
    assert(routeGraph.hasPath({stationA, stationB, stationC}, 1) == true);
    assert(routeGraph.hasPath({stationA, stationC}, 1) == false);

  

*/
/*int main() {
    Station stationA("A", "Moscow");
    Station stationB("B", "St.Petersburg");
    Station stationC("C", "Perm");

    RouteGraph routeGraph;
    routeGraph.addPath(stationA, stationB, 10);
    routeGraph.addPath(stationB, stationC, 15);

    // Добавление расписания движения для поезда 1
    vector<pair<Station, int>> route1 = {{stationA, 100}, {stationB, 200}, {stationC, 300}};

    Train train1;
    train1.setNumber(1);
    train1.setStartTime(800);
    train1.setSpeed(2);
    train1.setRoute(route1);

    // Вывод информации о маршруте
    cout << "Route information for Train 1:" << endl;
    cout << "Train Number: " << train1.getNumber() << endl;
    cout << "Start Time: " << train1.getStartTime() << endl;
    cout << "Route:" << endl;
    for (const auto& step : train1.getRoute()) {
        cout << "  Station: " << step.first.getName() << ", Time: " << step.second << endl;
    }

    

    // Проверка маршрута в графе
    

    // Добавление расписания в расписание поездов
    routeGraph.addSchedule(train1);


    Train train4;
    train4.setNumber(4);
    train4.setStartTime(2);
    train4.setSize(100);
    vector<pair<Station, int>> route3 = {{stationC, 500}, {stationB, 610}, {stationC, 700}};
    train4.setRoute(route3);
    routeGraph.addSchedule(train4);

    Train train6;
    train6.setNumber(6);
    train6.setStartTime(2);
    train6.setSize(100);
    vector<pair<Station, int>> route5 = {{stationC, 500}, {stationB, 610}, {stationC, 700}};
    train6.setRoute(route5);
    routeGraph.addSchedule(train6);

    // Вывод информации о расписании

    return 0;
}
*/

