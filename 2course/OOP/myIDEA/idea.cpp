#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

/*
Custom exception classes are defined for different types of issues that can
occur in the system.
*/
enum class IssueCategory {
    SecurityBreach,
    SystemMalfunction,
    ResourceAllocation,
    CommunicationError
};

class SecurityBreachException : public exception {
public:
    const char* what() const throw() override {
        return "Security breach detected.";
    }
};

class DataAccessException : public exception {
public:
    const char* what() const throw() override { return "Data access violation."; }
};

class CommunicationError : public exception {
public:
    const char* what() const throw() override {
        return "Failed to establish communication.";
    }
};

/*
The ICommunicable interface defines the basic communication methods that can be
implemented by classes that need to communicate with the Core.
*/
class ICommunicable {
public:
    virtual void connect_to_core() = 0;
    virtual void disconnect_from_core() = 0;
    virtual void transmit_data() = 0;
    virtual void receive_data() = 0;
    virtual ~ICommunicable() {}
};

// TODO: Move all logging here
class Loggable {
protected:
    static void log(const string& message) { cout << "Log: " << message << endl; }

    static void error(const string& message) {
        cout << "Error: " << message << endl;
    }

    static void warning(const string& message) {
        cout << "Warning: " << message << endl;
    }

    static void info(const string& message) {
        cout << "Info: " << message << endl;
    }

    static void general_alert(const string& message) {
        cout << "Alert: " << message << endl;
    }

    static void security_alert(const string& message) {
        cout << "Security Alert: " << message << endl;
    }
};


class CityManager : public Loggable {
public:
    void start_city() { log("City operations started."); }

    void restructure_city() {
        log("City structure is being transformed into the Glowing Labyrinth.");
    }

    void activate_emergency_protocols() {
        log("Emergency protocols activated due to threat detection.");
    }

    void allocate_resources(string resource, int amount) {
        log("Allocating " + to_string(amount) + " units of " + resource +
            " to necessary facilities.");
    }
};

class CityMonitor : public Loggable {
public:
    void monitor_city() {
        general_alert("Monitoring city activities and anomalies.");
    }

    void detect_anomalies() {
        general_alert("Anomaly detected! Analyzing potential threats.");
    }

    void alert_system(string alert) {
        general_alert("Alert: " + alert + " - Notifying core and city manager.");
    }
};

class CityProtector : public Loggable {
public:
    void protect_air() { security_alert("Air protection systems activated."); }

    void activate_defenses() {
        security_alert("Defenses activated to counteract threats.");
    }

    void implement_recovery_protocols() {
        security_alert(
            "Recovery protocols initiated to restore normal operations.");
    }
};

/*
Each class in the system has a specific role in the city's operations.
To preserve Single Responsibility Principle (SRP), each class is designed
to handle a specific set of operations.
*/
class Core {
private:
    unique_ptr<CityManager> manager;
    unique_ptr<CityMonitor> monitor;
    unique_ptr<CityProtector> protector;
    vector<ICommunicable*> reflectors;
    bool operational_status;

public:
    Core()
        : manager(make_unique<CityManager>()),
        monitor(make_unique<CityMonitor>()),
        protector(make_unique<CityProtector>()), operational_status(false) {}

    void register_reflector(ICommunicable* reflector) {
        reflectors.push_back(reflector);
        cout << "Reflector registered with the core." << endl;
    }

    void deregister_reflector(ICommunicable* reflector) {
        reflectors.erase(remove(reflectors.begin(), reflectors.end(), reflector),
                         reflectors.end());
        cout << "Reflector deregistered from the core." << endl;
    }

    static void display_system_status(bool status) {
        cout << "System status: " << (status ? "Operational" : "Non-Operational")
            << endl;
    }

    void start_system() {
        manager->start_city();
        monitor->monitor_city();
        protector->protect_air();
        cout << "System is fully operational." << endl;
    }

    void evolve() {
        try {
            cout << "Core is evolving, integrating new technologies." << endl;

            // TODO: Dynamically determine resources to allocate
            int resourceAmount = calculate_resource_needs();
            manager->allocate_resources("QPU", resourceAmount);
            update_operational_status();
            notify_reflectors();
        }
        catch (const exception& e) {
            cout << "Exception during evolution: " << e.what() << endl;
            operational_status = false;
            display_system_status(operational_status);
        }
    }

    void restructure_and_monitor() {
        try {
            if (!operational_status) {
                throw SecurityBreachException();
            }
            manager->restructure_city();
            monitor->monitor_city();
            cout << "Restructuring and monitoring tasks are running." << endl;
        }
        catch (const SecurityBreachException& e) {
            cout << "Exception caught in restructure_and_monitor: " << e.what()
                << endl;
            // Handle security breach, disable the system
            operational_status = false;
            display_system_status(operational_status);
        }
    }

    void report_issue(const string& issue) {
        cout << "Issue reported: " << issue << ". Addressing immediately." << endl;
        IssueCategory category = categorize_issue(issue);
        handle_issue(category);
    }

    IssueCategory categorize_issue(const string& issue) {
        if (issue.find("breach") != string::npos) {
            return IssueCategory::SecurityBreach;
        }
        else if (issue.find("malfunction") != string::npos) {
            return IssueCategory::SystemMalfunction;
        }
        else if (issue.find("allocation") != string::npos) {
            return IssueCategory::ResourceAllocation;
        }
        else if (issue.find("communication") != string::npos) {
            return IssueCategory::CommunicationError;
        }
        return IssueCategory::SystemMalfunction;
    }

    void handle_issue(IssueCategory category) {
        switch (category) {
        case IssueCategory::SecurityBreach:
            cout << "Initiating security lockdown." << endl;
            manager->activate_emergency_protocols();
            break;
        case IssueCategory::SystemMalfunction:
            cout << "Checking system components for malfunctions." << endl;
            break;
        case IssueCategory::ResourceAllocation:
            cout << "Reviewing resource allocation strategies." << endl;
            break;
        case IssueCategory::CommunicationError:
            cout << "Attempting to re-establish communication links." << endl;
            break;
        default:
            cout << "General maintenance protocol initiated." << endl;
            break;
        }
    }

    void change_operational_status(bool status) {
        operational_status = status;
        display_system_status(operational_status);
    }

    friend ostream& operator<<(ostream& os, const Core& core) {
        os << "Core operational status: "
            << (core.operational_status ? "Operational" : "Non-Operational");
        return os;
    }

    void notify_reflectors() {
        for (ICommunicable* reflector : reflectors) {
            reflector->receive_data();
        }
    }

    // ! JUST FOR TASK... Pre-increment:
    Core& operator++() {
        operational_status = true;
        cout << "Core operational status set to online via prefix increment."
            << endl;
        return *this;
    }

    // ! JUST FOR TASK... Post-increment:
    Core& operator++(int) {
        cout << "Core is evolving via postfix increment." << endl;
        this->evolve();
        return *this;
    }

private:
    // TODO: Maybe add logic?)
    void update_operational_status() {
        operational_status = true;
        display_system_status(operational_status);
    }

    // TODO: Maybe add logic?)
    int calculate_resource_needs() { return 50; }
};

class Reflector : public ICommunicable {
protected:
    unique_ptr<string> chromatic_clothing;
    unique_ptr<string> personal_data;
    bool isConnected;
    Core& core;

public:
    string name;

    // Default Constructor
    Reflector(Core& coreInstance)
        : name("Default Reflector"), core(coreInstance),
        chromatic_clothing(make_unique<string>("Standard")),
        personal_data(make_unique<string>("Generic")) {}

    // Constructor with Name
    Reflector(const string& name, Core& coreInstance)
        : name(name), core(coreInstance),
        chromatic_clothing(make_unique<string>("Variable")),
        personal_data(make_unique<string>("Confidential")) {}

    // Detailed Constructor
    Reflector(const string& name, const string& clothingColor,
              const string& pData, Core& coreInstance)
        : name(name), core(coreInstance),
        chromatic_clothing(make_unique<string>(clothingColor)),
        personal_data(make_unique<string>(pData)) {}

    void blend_in() {
        cout << name << " blends into the city environment using "
            << *chromatic_clothing << endl;
    }

    void communicate() {
        if (!isConnected) {
            cout << name
                << " cannot communicate because it is not connected to the Core."
                << endl;
            throw CommunicationError();
        }
        try {
            cout << name << " communicates using Lightlinks." << endl;
            core.notify_reflectors();
        }
        catch (const exception& e) {
            cout << "Communication error: " << e.what() << endl;
        }
    }

    void connect_to_core() override {
        cout << name << " connects to the Core." << endl;
        core.register_reflector(this);
        isConnected = true;
    }

    void disconnect_from_core() override {
        cout << name << " safely disconnects from the Core." << endl;
        core.deregister_reflector(this);
        isConnected = false;
    }

    void transmit_data() override {
        cout << name << " transmits data." << endl;
        core.report_issue(name + " has transmitted critical data.");
    }

    void receive_data() override {
        cout << name << " receives operational data from Core." << endl;
    }
};

class Shatter : public Reflector {
private:
    unique_ptr<string> hacking_skills;
    unique_ptr<string> real_name;

public:
    string fake_name;

    Shatter(string fakeName, string realName, string reflectorName,
            Core& coreInstance)
        : Reflector(reflectorName, coreInstance), fake_name(fakeName),
        hacking_skills(make_unique<string>("Advanced")),
        real_name(make_unique<string>(realName)) {}

    void communicate() {
        cout << name << " secretly communicates using encrypted channels." << endl;
    }

    void hack_system() {
        cout << name << " is attempting to hack into the city's mainframe." << endl;
    }

    void disrupt_operations() {
        cout << fake_name << " is disrupting city operations." << endl;
        core.report_issue(fake_name + " has initiated a disruption.");
    }

    void evade_monitoring() {
        cout << fake_name << " is evading surveillance systems." << endl;
    }

    void neutralize_protections() {
        cout << fake_name << " is attempting to neutralize city protections."
            << endl;
    }
};

// ! JUST FOR TASK... Overloading == operator(non-member function):
bool operator==(const Reflector& lhs, const Reflector& rhs) {
    return lhs.name == rhs.name;
}

int main() {
    try {
        Core central_core;
        Core task_only_core;

        // Starting city operations
        cout << "----- Initializing City Operations -----" << endl;
        central_core.start_system();

        // Using the prefix increment operator
        cout << "\n----- Prefix Increment Operator Demonstration(ONLY FOR TASK) -----" << endl;
        cout << "Before prefix increment: " << task_only_core << endl;
        ++task_only_core;
        cout << "After prefix increment: " << task_only_core << endl;

        // Using the postfix increment operator
        cout << "\n----- Postfix Increment Operator Demonstration(ONLY FOR TASK) -----" << endl;
        cout << "Before postfix increment: " << task_only_core << endl;
        task_only_core++;
        cout << "After postfix increment: " << task_only_core << endl;

        // Use default constructor to create a Reflector
        Reflector defaultReflector(central_core);
        cout << "\n----- Reflector Interaction(default constructor) -----" << endl;
        defaultReflector.connect_to_core();
        defaultReflector.communicate();
        defaultReflector.transmit_data();

        // Creating a Reflector with a name
        Reflector johnDoe("John Doe", central_core);
        cout << "\n----- Reflector Interaction(with a name) -----" << endl;
        johnDoe.connect_to_core();
        johnDoe.communicate();
        johnDoe.transmit_data();

        // Use detailed constructor
        Reflector detailedReflector("FishEye Placebo", "Silver",
                                    "Highly Confidential", central_core);
        cout << "\n----- Reflector Interaction(detailed constructor) -----" << endl;
        detailedReflector.connect_to_core();
        detailedReflector.communicate();
        detailedReflector.transmit_data();
        // detailedReflector.disconnect_from_core();

        // Show == operator overloading
        cout << "\n----- Reflector Equality Check(ONLY FOR TASK) -----" << endl;
        cout << "Are defaultReflector and johnDoe the same? "
            << (defaultReflector == johnDoe ? "Yes" : "No") << endl;


        // Creating a Shatter and causing disturbances
        Shatter rogue("Rogue", "Unknown", "Rebel One", central_core);
        cout << "\n----- Shatter Disruption -----" << endl;
        rogue.disrupt_operations();
        rogue.evade_monitoring();
        rogue.neutralize_protections();

        // City's reaction to disruptions
        cout << "\n----- City Monitoring and Protection Reaction -----" << endl;
        central_core.restructure_and_monitor();
        central_core.evolve();

        // Simulate recovery protocols by CityProtector
        cout << "\n----- Initiating Recovery Protocols -----" << endl;
        CityProtector cityProtector;
        cityProtector.implement_recovery_protocols();

    }
    catch (const SecurityBreachException& e) {
        cout << "Security Exception: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "Standard Exception: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown Exception occurred." << endl;
    }

    return 0;
}