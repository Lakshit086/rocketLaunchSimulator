// By encapsulating user input commands and running matching methods
//  in the RocketLaunchSimulator class, the code displays
//  traits of the Command design pattern.

/*----------------------The Code begins--------------*/
#include<bits/stdc++.h>
using namespace std;

// Rocket Launch Simulator Class which contains the methods as per the given exercise.
class RocketLaunchSimulator {
private:
    string stage;     // Current stage of the rocket
    int fuel;         // Remaining fuel percentage
    int altitude;     // Current altitude in kilometers
    int speed;        // Current speed in km/h
    
public:
    // A constructor which will invoke as soon as the  object is created.
    RocketLaunchSimulator() : stage("Pre-Launch"), fuel(100), altitude(0), speed(0) {}

    // This method start_checks will perform the checks need to perform before the launch. 
    void startChecks() {
        if (stage == "Pre-Launch") {
            cout << "Performing pre-launch checks..." << endl;
            if (checksPassed()) {
                cout << "All systems are 'Go' for launch." << endl;
            } else {
                cout << "Pre-launch checks failed. Cannot launch." << endl;
            }
        } else {
            cout << "Cannot perform pre-launch checks during flight." << endl;
        }
    }

    // Method launch will launch the rocket if all the checks have been passed successfully which will be the stage 1.
    void launch() {
        if (stage == "Pre-Launch" && checksPassed()) {
            cout << "Launching..." << endl;
            stage = "Stage 1";
            updateStage();
        } else {
            cout << "Cannot launch. Perform pre-launch checks first or already in flight." << endl;
        }
    }

    // fastForward method will calculate and display the updated parameters after X seconds.
    void fastForward(int seconds) {
        if (stage == "Pre-Launch") {
            cout << "Cannot fast forward before launch." << endl;
        } else if (stage != "Mission Failed" && stage != "Mission Successful") {
            cout << "Fast Forwarding " << seconds << " seconds..." << endl;
            for (int i = 0; i < seconds; ++i) {
                updateStage();
                // sleep time for 1 sec
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
    }

    // The most important function updateStage
    // which will update the state of the rocket every second and display it to the user screen.
    void updateStage() {
        if (stage != "Mission Failed" and stage != "Mission Successful") {
            fuel -= 10;
            altitude += 10;
            speed += 1000;

            cout << "Stage: " << stage << ", Fuel: " << fuel << "%, Altitude: " << altitude << " km, Speed: " << speed << " km/h" << endl;

            if (fuel <= 0) {
                stage = "Mission Failed";
                cout << "Mission Failed due to insufficient fuel." << endl;
            } 
            // once the altitude is reached above 90km we will assume rocket has achieved it's orbit. 
            // #MissonSuccessful
            else if (altitude >= 90) {
                cout<<"Stage 1 complete. Separating stage. Entering Stage 2."<<endl;
                stage = "Mission Successful";
                cout << "Orbit achieved! Mission Successful." << endl;
            }
        }
    }

    // We can add basic checks for pre-launch.
    // Placeholder for adding checks for rocket launch
    bool checksPassed() {
        return fuel >= 100;
    }
};

int main() {
    // Creating RocketLaunch simulator 
    RocketLaunchSimulator simulator;
    cout<<endl;
    cout<<"***************************Rocket Launch Simulator**************************"<<endl;
    while (true) {
        // You need to enter the command start_checks/launch/fast_forward
        // If you choose fast_forward then terminal will ask you to enter number of seconds you want to skip the progress tracing.
        // quit command will help you to terminate the code.

        string command;
        cout<<endl;
        cout << "Enter any one of the command (startChecks, launch, fastForward X, quit): ";
        cin >> command;

        if (command == "startChecks") {
            simulator.startChecks();
        } else if (command == "launch") {
            simulator.launch();
        } else if (command == "fastForward") {
            int seconds;
            cin >> seconds;
            simulator.fastForward(seconds);
        } else if (command == "quit") {
            break;
        } else {
            cout << "Invalid command!!. Please enter Valid commands as 'startChecks', 'launch', 'fastForward X', and 'quit'." << endl;
        }
    }

    return 0;
}
/*----------------------The Code ends--------------*/