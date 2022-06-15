#include <iostream>
#include <string>

class Country {
    public:
        Country() {
            this->name = "";
            this->goldMedals = -1;
            this->silverMedals = -1;
            this->bronzeMedals = -1;
        }

        Country(std::string countryName,
                int goldMedals,
                int silverMedals,
                int bronzeMedals) {
            
            this->name = countryName;
            this->goldMedals = goldMedals;
            this->silverMedals = silverMedals;
            this->bronzeMedals = bronzeMedals;
        }

        bool operator < (Country const country) {
            if (this->goldMedals < country.goldMedals) return true;
            else if (this->goldMedals > country.goldMedals) return false;

            if (this->silverMedals < country.silverMedals) return true;
            else if (this->silverMedals > country.silverMedals) return false;

            if (this->bronzeMedals < country.bronzeMedals) return true;
            else if (this->bronzeMedals > country.bronzeMedals) return false;

            return false;
        }

        bool operator > (Country const country) {
            if (this->goldMedals > country.goldMedals) return true;
            else if (this->goldMedals < country.goldMedals) return false;

            if (this->silverMedals > country.silverMedals) return true;
            else if (this->silverMedals < country.silverMedals) return false;

            if (this->bronzeMedals > country.bronzeMedals) return true;
            else if (this->bronzeMedals < country.bronzeMedals) return false;

            return false;
        }

        bool operator == (Country const country) {
            if (this->goldMedals != country.goldMedals) return false;
            if (this->silverMedals != country.silverMedals) return false;
            if (this->bronzeMedals != country.bronzeMedals) return false;
            
            return true;
        }

        std::string getName() {
            return this->name;
        }

        void print() {
            std::cout << this->name << " ";
            std::cout << this->goldMedals << " ";
            std::cout << this->silverMedals << " ";
            std::cout << this->bronzeMedals << std::endl;
        }

    private:
        std::string name;
        int goldMedals;
        int silverMedals;
        int bronzeMedals;

    friend class OlimpicCountries;
};

class OlimpicCountries {
    public:
        OlimpicCountries() {
            this->countriesAmount = -1;
            countries = nullptr;
        }

        OlimpicCountries(int countriesAmount) {
            this->countriesAmount = countriesAmount;
            countries = new Country*[countriesAmount];
        }

        ~OlimpicCountries() {
            delete []this->countries;
            this->countries = nullptr;
        }

        void addCountry(int pos, std::string name, int gM, int sM, int bM) {
            this->countries[pos] = new Country(name, gM, sM, bM);
        }

        void merge(int left, int mid, int right) {
            int subArrayOne = mid - left + 1;
            int subArrayTwo = right - mid;

            Country **leftArray = new Country*[subArrayOne];
            Country **rightArray = new Country*[subArrayTwo];
        
            for (int i = 0; i < subArrayOne; i++)
                leftArray[i] = this->countries[left + i];
            for (int j = 0; j < subArrayTwo; j++)
                rightArray[j] = this->countries[mid + 1 + j];
        
            int indexOfSubArrayOne = 0;
            int indexOfSubArrayTwo = 0;
            int indexOfMergedArray = left;
        
            while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
                if (*leftArray[indexOfSubArrayOne] > *rightArray[indexOfSubArrayTwo]) {
                    this->countries[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                    indexOfSubArrayOne++;
                }
                else if (*leftArray[indexOfSubArrayOne] == *rightArray[indexOfSubArrayTwo] && 
                          leftArray[indexOfSubArrayOne]->getName() <= rightArray[indexOfSubArrayTwo]->getName()) {
                    this->countries[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                    indexOfSubArrayOne++;
                }
                else {
                    this->countries[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                    indexOfSubArrayTwo++;
                }
                indexOfMergedArray++;
            }

            while (indexOfSubArrayOne < subArrayOne) {
                this->countries[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
                indexOfMergedArray++;
            }

            while (indexOfSubArrayTwo < subArrayTwo) {
                this->countries[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
                indexOfMergedArray++;
            }
        }

        void mergeSort(int begin, int end) {
            if (begin >= end) return;
        
            int mid = begin + (end - begin) / 2;
            this->mergeSort(begin, mid);
            this->mergeSort(mid + 1, end);

            this->merge(begin, mid, end);
        }

        void printCountries() {
            this->mergeSort(0, this->countriesAmount - 1);

            for (int i = 0; i < this->countriesAmount; i++) {
                this->countries[i]->print();
            }
            
        }

    private:
        int countriesAmount;
        Country **countries;
};

int main() {
    int countriesAmount;
    OlimpicCountries *olimpics;

    std::cin >> countriesAmount;
    olimpics = new OlimpicCountries(countriesAmount);

    for (int i = 0; i < countriesAmount; i++) {
        int gM, sM, bM;
        std::string name;

        std::cin >> name >> gM >> sM >> bM;

        olimpics->addCountry(i, name, gM, sM, bM);
    }

    olimpics->printCountries();

    delete olimpics;
    olimpics = nullptr;
    return 0;
}