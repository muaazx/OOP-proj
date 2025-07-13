#include <iostream>
#include <vector>   
#include <string>
#include <iomanip>  //Sets decimal precision for floating-point numbers

using namespace std;

// Lawyer class
class Lawyer {
private:
    string name;
    string specialty;
    int experience;
    float rating;
    int totalRatings;
    double fee;

public:
    Lawyer(string n, string s, int e, float r, double f)
        : name(n), specialty(s), experience(e), rating(r), totalRatings(1), fee(f) {}  // at least one review (totalRatings)

    void displayInfo(int index) const {  // won’t accidentally modify the object
        cout << index << ". " << name
             << " | Experience: " << experience << " yrs"
             << " | Rating: " << fixed << setprecision(1) << rating
             << " | Fee: $" << fixed << setprecision(2) << fee << endl;
    }

    string getName() const { return name; }
    string getSpecialty() const { return specialty; }
    double getFee() const { return fee; }

    //Counter offer logic
    // If the user offer is less than the fee, return a counter offer based on the fee.
    double getCounterOffer(double offer) const {
        double minAcceptable = fee * 0.9;
        if (offer >= fee) return offer;
        else if (offer >= minAcceptable) return offer;
        else return fee * 0.9;
    }

    // Add a rating and update the average rating
    // The first rating initializes the average rating.
    void addRating(float newRating) {
        rating = ((rating * totalRatings) + newRating) / (totalRatings + 1);
        totalRatings++;
    }
};

// User class
class User {
private:
    string name, email, gender, phone, role;

public:
    void inputUserInfo() {
        cin.ignore();
        cout<< "==== Law Connect System ===="<<endl;
        cout << "\nEnter your details:\n";
        cout << "Full Name: ";
        getline(cin, name);
        cout << "Email: ";
        getline(cin, email);
        cout << "Gender: ";
        getline(cin, gender);
        cout << "Phone Number: ";
        getline(cin, phone);
        cout << "Are you a Plaintiff or Defendant? ";
        getline(cin, role);
    }

    void displayUserInfo() const {
        cout << "\n\U0001F464 User Info:\n"
             << "Name: " << name << "\n"
             << "Email: " << email << "\n"
             << "Gender: " << gender << "\n"
             << "Phone: " << phone << "\n"
             << "Role: " << role << endl;
    }
};

// Case base class
class Case {
protected:                  //protected allows child classes to access and use these members
    string caseType;
    string description;

public:
    virtual void inputDetails() {                //Virtual will allow derived classes to override this method (Will choose case type)
        cout << "\nEnter case description: ";
        cin.ignore();                            //Ignores everything until the next newline (even long input)
        getline(cin, description);
    }

    string getType() const { return caseType; }
    string getDescription() const { return description; }

    virtual ~Case() {}        // Virtual destructor for proper cleanup of derived classes
    // This ensures that when a Case pointer is deleted, the correct derived class destructor is called.
};

// Case types
class CivilCase : public Case {
public:
    CivilCase() { caseType = "Civil"; }
};

class CriminalCase : public Case {
public:
    CriminalCase() { caseType = "Criminal"; }
};

class FamilyCase : public Case {
public:
    FamilyCase() { caseType = "Family"; }
};

// Law Connect System
class LawConnectSystem {
private:
    vector<Lawyer> lawyers;     //Store multiple Lawyer objects
                                //Grow/shrink dynamically as needed
                                //Be easily iterated, searched, sorted, etc.

    void printTrialDate() {
        cout << "\U0001F4C5 Your first trial date is scheduled for 20th June 2025.\n";
    }

public:
    LawConnectSystem() {
        lawyers.emplace_back("Gohar Khan", "Civil", 10, 4.5, 500.0);     //Emplace_back
        lawyers.emplace_back("Aitezaz Hasan", "Criminal", 8, 4.7, 750.0);     //Constructs the object directly inside the vector
        lawyers.emplace_back("Sher Afzal Marwat", "Family", 5, 4.2, 300.0);
        lawyers.emplace_back("Shehryar Ahmed Khan", "Civil", 7, 4.0, 450.0);
        lawyers.emplace_back("Muaaz Ahmed", "Criminal", 12, 4.9, 900.0);
        lawyers.emplace_back("Eman Mazari", "Criminal", 7, 4.1, 350.0);
        lawyers.emplace_back("Sanaullah Khan", "Family", 6, 4.3, 400.0);
        lawyers.emplace_back("Ali Raza", "Civil", 9, 4.6, 600.0);
        lawyers.emplace_back("Fatima Bibi", "Family", 4, 3.8, 250.0);
        lawyers.emplace_back("Zaryab Ali", "Criminal", 3, 4.0, 200.0);
        lawyers.emplace_back("Bilal Khan", "Civil", 11, 4.8, 550.0);
        lawyers.emplace_back("Saad Ahmed", "Family", 2, 3.5, 150.0);
        lawyers.emplace_back("Usman Tariq", "Criminal", 6, 4.4, 400.0);
        lawyers.emplace_back("Hassan Malik", "Civil", 5, 4.3, 300.0);
        lawyers.emplace_back("Asad Ali", "Family", 8, 4.6, 700.0);
        lawyers.emplace_back("Shoaib Khan", "Criminal", 10, 4.9, 800.0);
        lawyers.emplace_back("Owais Ahmed", "Civil", 9, 4.5, 600.0);
        lawyers.emplace_back("Ayesha Bibi", "Family", 4, 3.9, 250.0);
        lawyers.emplace_back("Tariq Jamil", "Criminal", 7, 4.2, 350.0);
        lawyers.emplace_back("Fayaz Khan", "Civil", 3, 4.0, 200.0);
        lawyers.emplace_back("Faisal Raza", "Family", 6, 4.1, 400.0);
        lawyers.emplace_back("Talha Ahmed", "Criminal", 5, 5.0, 1000.0);
    }

    void start() {
        User user;
        user.inputUserInfo();

        int choice;
        Case* userCase = nullptr;  //A pointer to a base class `Case`, used polymorphically
                                   //Using a pointer to the base class (Case*) allows you to call virtual functions like this

        cout << "Select Case Type:\n";
        cout << "1. Civil\n2. Criminal\n3. Family\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: userCase = new CivilCase(); break;
            case 2: userCase = new CriminalCase(); break;
            case 3: userCase = new FamilyCase(); break;
            default:
                cout << "Invalid case type.\n";
                return;
        }

        userCase->inputDetails();
        user.displayUserInfo();
        cout << "\n\U0001F4C4 Case Description: " << userCase->getDescription() << endl;

        // Filtering list of lawyers according to the case type
        vector<Lawyer*> matched;  //Creates an empty vector named matched
        for (auto& lawyer : lawyers) {    //Loops through every Lawyer object in the lawyers vector //using (&) to avoid copying //Range-Based Loop
            if (lawyer.getSpecialty() == userCase->getType()) { //If both match, that lawyer is suitable for the case
                matched.push_back(&lawyer);  //If the condition is true, it adds the address of the lawyer to the matched vector
            }  //push_back: Adds an existing object
        } //We only need a reference to the lawyer for display, selection, or further action

        if (matched.empty()) {  //Checks if the matched vector is empty (i.e., size is 0)
            cout << "\u274C No lawyers available for this case type.\n";
            delete userCase;  //Clean up the dynamically allocated case object
            return;
        }

        bool dealDone = false;
        while (!dealDone && !matched.empty()) {     //Loop until a deal is done or no lawyers are left
            cout << "\n\U0001F50D Available Lawyers:\n";
            for (size_t i = 0; i < matched.size(); ++i) {
                matched[i]->displayInfo(i + 1);
            }

            int lawyerChoice;
            cout << "Select a lawyer (1 to " << matched.size() << ", or 0 to cancel): ";
            cin >> lawyerChoice;

            if (lawyerChoice == 0) {
                cout << "Cancelled. Returning to main menu.\n";
                break;
            }

            if (lawyerChoice < 1 || lawyerChoice > matched.size()) {
                cout << "Invalid selection.\n";
                continue;
            }

            Lawyer* selected = matched[lawyerChoice - 1];
            double userOffer;
            cout << "\nEnter your proposed budget for " << selected->getName() << ": $";
            cin >> userOffer;

            double counter = selected->getCounterOffer(userOffer);

            if (userOffer >= selected->getFee() || counter == userOffer) {
                cout << "\u2705 Deal confirmed with " << selected->getName() << " at $" << userOffer << ".\n";
                printTrialDate();
                dealDone = true;

                float stars;
                cout << "\nPlease rate your lawyer (1.0 to 5.0): ";
                cin >> stars;
                while (stars < 1.0 || stars > 5.0) {
                    cout << "Invalid rating. Try again: ";
                    cin >> stars;
                }
                selected->addRating(stars);
                cout << "\u2B50 Thank you! Your review has been recorded.\n";
            } else {
                cout << "\u2696\uFE0F  Counter offer from " << selected->getName() << ": $" << counter << endl;
                char reply;
                cout << "Do you accept the counter offer? (y/n): ";
                cin >> reply;
                if (reply == 'y' || reply == 'Y') {
                    cout << "\u2705 Deal confirmed at $" << counter << ".\n";
                    printTrialDate();
                    dealDone = true;

                    float stars;
                    cout << "\nPlease rate your lawyer (1.0 to 5.0): ";
                    cin >> stars;
                    while (stars < 1.0 || stars > 5.0) {
                        cout << "Invalid rating. Try again: ";
                        cin >> stars;
                    }
                    selected->addRating(stars);
                    cout << "\u2B50 Thank you! Your review has been recorded.\n";
                } else {
                    cout << "\u274C You rejected the offer. This lawyer will no longer be shown.\n";
                    matched.erase(matched.begin() + (lawyerChoice - 1));
                }
            }

            if (!dealDone && matched.empty()) {
                cout << "\n\u274C No more lawyers available. Ending session.\n";
            }
        }

        delete userCase;
    }
};

// Main function
int main() {
    LawConnectSystem system;
    system.start();
    return 0;
}