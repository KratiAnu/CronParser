#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>
#include <algorithm>

const std::string fieldNames[] = {"minute", "hour", "day of month", "month", "day of week"};

class CronParser {
public:
    static std::vector<int> expandField(const std::string& field, int max_value) {
        try {
            if (field == "*") {
                return expandRange(0, max_value);
            }
            if(field=="/"||field=="-"||field==" ")
            	return {};

            size_t slash_pos = field.find('/');
            if (slash_pos != std::string::npos) {
            	int step = std::stoi(field.substr(slash_pos + 1));//to add case when negative numbers of undefined numbers
                return expandStep(0, max_value, step);// : {};
            }

            size_t dash_pos = field.find('-');
            if (dash_pos != std::string::npos) {
                return expandRange(std::stoi(field.substr(0, dash_pos)),
                                   std::stoi(field.substr(dash_pos + 1)) + 1);
            }
			
			if(!isNumeric(field)){
				throw std::invalid_argument("Invalid field format");
			}
            return {std::stoi(field)>0};
        } catch (const std::invalid_argument&) {
            throw std::invalid_argument("Invalid field format");
        }
    }
    
    static bool isNumeric(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

    static std::vector<int> expandRange(int start, int end) {
        std::vector<int> result(end - start);
        for (int i = start; i < end; ++i) {
            result[i - start] = i;
        }
        return result;
    }

    static std::vector<int> expandStep(int start, int max_value, int step) {
        std::vector<int> result;
        for (int i = start; i < max_value; i += step) {
            result.push_back(i);
        }
        return result;
    }

    static std::vector<int> splitField(const std::string& field, char delimiter) {
        std::istringstream iss(field);
        std::vector<std::string> tokens;
        std::copy(std::istream_iterator<std::string>(iss),
                  std::istream_iterator<std::string>(),
                  std::back_inserter(tokens));

        std::vector<int> result;
        for (const auto& token : tokens) {
            try {
                result.push_back(std::stoi(token));
            } catch (const std::invalid_argument&) {
                throw std::invalid_argument("Invalid field format");
            }
        }
        return result;
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Error: " << argv[0] << "Invalid args" << std::endl;
        return 1;
    }

    std::string cron_string = argv[1];//"*/2 0 1 * 1-5 /usr/bin/fin";

    std::istringstream iss(cron_string);
    std::vector<std::string> fields(std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>());

    try {
        for (int i = 0; i < 5; ++i) {
            std::cout << std::left << std::setw(13) << fieldNames[i];
            std::vector<int> values = i < fields.size() ? CronParser::expandField(fields[i], i == 0 ? 60 : (i == 1 ? 24 : (i == 2 ? 32 : (i == 3 ? 13 : 7)))) : std::vector<int>();
            
            if(values.size()>0)
            for (int value : values) {
                std::cout << value << ' ';
            }
            std::cout << std::endl;
        }

        std::cout << "command      " << (fields.size() == 6 ? fields[5] : "") << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}