#include <string>
#include <iostream>
#include <vector>

// Абстрактный базовый класс для всех транспортных средств
class AbstractVehicle {
protected:
    std::string _manufacturer;  // Производитель
    std::string _model;         // Модель
    int _year;                  // Год выпуска
    double _price;              // Цена в долларах

public:
    AbstractVehicle(const std::string& manufacturer, const std::string& model, int year, double price)
        : _manufacturer(manufacturer), _model(model), _year(year), _price(price) {}

    // Виртуальный метод для вывода информации (должен быть реализован в производных классах)
    virtual void DisplayInfo() const = 0;

    // Виртуальный метод для получения типа транспортного средства
    virtual std::string GetVehicleType() const = 0;

    // Геттер для цены
    double GetPrice() const {
        return _price;
    }

    virtual ~AbstractVehicle() = default; // Виртуальный деструктор для корректного удаления объектов
};

// Базовый класс для автомобилей
class Car : public AbstractVehicle {
protected:
    int _doors;         // Количество дверей
    double _engineSize; // Объем двигателя в литрах
    std::string _fuelType; // Тип топлива

public:
    Car(const std::string& manufacturer, const std::string& model, int year, double price,
        int doors, double engineSize, const std::string& fuelType)
        : AbstractVehicle(manufacturer, model, year, price),
        _doors(doors), _engineSize(engineSize), _fuelType(fuelType) {}

    void DisplayInfo() const override {
        std::cout << GetVehicleType() << " - " << _manufacturer << " " << _model 
                << " (" << _year << "), Price: $" << _price 
                << ", Doors: " << _doors << ", Engine: " << _engineSize << "L"
                << ", Fuel: " << _fuelType << std::endl;
    }

    std::string GetVehicleType() const override {
        return "Car";
    }
};

// Класс для седанов
class Sedan : public Car {
private:
    double _trunkCapacity; // Объем багажника в литрах

public:
    Sedan(const std::string& manufacturer, const std::string& model, int year, double price,
        int doors, double engineSize, const std::string& fuelType, double trunkCapacity)
        : Car(manufacturer, model, year, price, doors, engineSize, fuelType),
        _trunkCapacity(trunkCapacity) {}

    void DisplayInfo() const override {
        Car::DisplayInfo();
        std::cout << "  Trunk capacity: " << _trunkCapacity << " liters" << std::endl;
    }

    std::string GetVehicleType() const override {
        return "Sedan";
    }
};

// Класс для внедорожников (SUV)
class SUV : public Car {
private:
    bool _fourWheelDrive; // Полный привод
    double _clearance;    // Дорожный просвет в мм

public:
    SUV(const std::string& manufacturer, const std::string& model, int year, double price,
        int doors, double engineSize, const std::string& fuelType, bool fourWheelDrive, double clearance)
        : Car(manufacturer, model, year, price, doors, engineSize, fuelType),
        _fourWheelDrive(fourWheelDrive), _clearance(clearance) {}

    void DisplayInfo() const override {
        Car::DisplayInfo();
        std::cout << "  4WD: " << (_fourWheelDrive ? "Yes" : "No") 
                << ", Clearance: " << _clearance << "mm" << std::endl;
    }

    std::string GetVehicleType() const override {
        return "SUV";
    }
};

// Класс для спортивных автомобилей
class SportsCar : public Car {
private:
    double _zeroToHundred; // Разгон 0-100 км/ч в секундах
    int _topSpeed;         // Максимальная скорость в км/ч

public:
    SportsCar(const std::string& manufacturer, const std::string& model, int year, double price,
        int doors, double engineSize, const std::string& fuelType, double zeroToHundred, int topSpeed)
        : Car(manufacturer, model, year, price, doors, engineSize, fuelType),
        _zeroToHundred(zeroToHundred), _topSpeed(topSpeed) {}

    void DisplayInfo() const override {
        Car::DisplayInfo();
        std::cout << "  0-100 km/h: " << _zeroToHundred << "s"
                << ", Top speed: " << _topSpeed << "km/h" << std::endl;
    }

    std::string GetVehicleType() const override {
        return "Sports Car";
    }
};

// Интерфейс для электромобилей
class IElectricVehicle {
public:
    virtual double GetBatteryCapacity() const = 0;  // Емкость батареи в кВт·ч
    virtual double GetRange() const = 0;            // Запас хода на одной зарядке
    virtual ~IElectricVehicle() = default;
};

// Класс для электромобилей (наследуется от Car и реализует IElectricVehicle)
class ElectricCar : public Car, public IElectricVehicle {
private:
    double _batteryCapacity; // Емкость батареи в кВт·ч
    double _range;           // Запас хода на одной зарядке в км

public:
    ElectricCar(const std::string& manufacturer, const std::string& model, int year, double price,
        int doors, double batteryCapacity, double range)
        : Car(manufacturer, model, year, price, doors, 0.0, "Electric"),
        _batteryCapacity(batteryCapacity), _range(range) {}

    void DisplayInfo() const override {
        std::cout << GetVehicleType() << " - " << _manufacturer << " " << _model 
                << " (" << _year << "), Price: $" << _price 
                << ", Doors: " << _doors 
                << ", Battery: " << _batteryCapacity << " kWh"
                << ", Range: " << _range << " km" << std::endl;
    }

    std::string GetVehicleType() const override {
        return "Electric Car";
    }

    double GetBatteryCapacity() const override {
        return _batteryCapacity;
    }

    double GetRange() const override {
        return _range;
    }
};

// Класс для автопарка организации
class Fleet {
private:
    std::vector<AbstractVehicle*> _vehicles; // Вектор указателей на транспортные средства

public:
    // Добавление транспортного средства в автопарк
    void AddVehicle(AbstractVehicle* vehicle) {
        _vehicles.push_back(vehicle);
    }

    // Вывод информации обо всех транспортных средствах
    void DisplayFleet() const {
        std::cout << "=== Fleet Overview ===" << std::endl;
        for (const auto& vehicle : _vehicles) {
            vehicle->DisplayInfo();
        }
    }

    // Расчет общей стоимости автопарка
    double CalculateTotalValue() const {
        double total = 0.0;
        for (const auto& vehicle : _vehicles) {
            total += vehicle->GetPrice();
        }
        return total;
    }

    // Деструктор для освобождения памяти
    ~Fleet() {
        for (auto vehicle : _vehicles) {
            delete vehicle;
        }
    }
};

int main() {
    // Создаем автопарк
    Fleet companyFleet;

    // Добавляем различные автомобили в автопарк
    companyFleet.AddVehicle(new Sedan("Toyota", "Camry", 2022, 25000, 4, 2.5, "Gasoline", 500));
    companyFleet.AddVehicle(new SUV("Ford", "Explorer", 2021, 35000, 5, 3.0, "Gasoline", true, 210));
    companyFleet.AddVehicle(new SportsCar("Porsche", "911", 2023, 120000, 2, 3.0, "Gasoline", 3.7, 320));
    companyFleet.AddVehicle(new ElectricCar("Tesla", "Model 3", 2023, 45000, 4, 75, 450));

    // Выводим информацию об автопарке
    companyFleet.DisplayFleet();

    // Выводим общую стоимость автопарка
    std::cout << "\nTotal fleet value: $" << companyFleet.CalculateTotalValue() << std::endl;

    return 0;
}