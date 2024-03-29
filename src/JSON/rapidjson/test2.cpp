#include "rapidjson/document.h" 

#include <iostream>

int main() 
{ 
	// Parse the JSON document 
	rapidjson::Document doc; 
	doc.Parse("{\"name\":\"John\",\"age\":30,\"city\":"
			"\"New York\"}"); 

	// Access the data in the document 
	if (doc.IsObject()) { 
		// Get the "name" member 
		if (doc.HasMember("name") 
			&& doc["name"].IsString()) { 
			std::string name = doc["name"].GetString(); 
			std::cout << "Name: " << name << std::endl; 
			// Output:- Name: John 
		} 

		// Get the "age" member 
		if (doc.HasMember("age") && doc["age"].IsInt()) { 
			int age = doc["age"].GetInt(); 
			std::cout << "Age: " << age << std::endl; 
			// Output:- Age: 30 
		} 

		// Get the "city" member 
		if (doc.HasMember("city") 
			&& doc["city"].IsString()) { 
			std::string city = doc["city"].GetString(); 
			std::cout << "City: " << city << std::endl; 
			// Output:- City: New York 
		} 
	} 

	return 0; 
}
