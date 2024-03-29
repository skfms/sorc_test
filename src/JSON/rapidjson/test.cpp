#include "rapidjson/document.h" 
#include "rapidjson/filereadstream.h" 

#include <cstdio> 
#include <iostream> 

int main() 
{ 
	// Open the file 
	FILE* fp = fopen("test.json", "rb"); 

	// Check if the file was opened successfully 
	if (!fp) { 
		std::cerr << "Error: unable to open file"
				<< std::endl; 
		return 1; 
	} 

	// Read the file into a buffer 
	char readBuffer[65536]; 
	rapidjson::FileReadStream is(fp, readBuffer, 
								sizeof(readBuffer)); 

	// Parse the JSON document 
	rapidjson::Document doc; 
	doc.ParseStream(is); 

	// Check if the document is valid 
	if (doc.HasParseError()) { 
		std::cerr << "Error: failed to parse JSON document"
				<< std::endl; 
		fclose(fp); 
		return 1; 
	} 

	// Close the file 
	fclose(fp); 

	// Access the data in the document 
	// Suppose the JSON document has the following 
	// structure: 
	// { 
	// "name": "John Smith", 
	// "age": 30, 
	// "city": "New York", 
	// "skills": ["programming", "guitar", "singing"] 
	// } 

	// Get the "name" member 
	if (doc.HasMember("name") && doc["name"].IsString()) { 
		std::string name = doc["name"].GetString(); 
		std::cout << "Name: " << name << std::endl; 
	} 

	// Get the "age" member 
	if (doc.HasMember("age") && doc["age"].IsInt()) { 
		int age = doc["age"].GetInt(); 
		std::cout << "Age: " << age << std::endl; 
	} 

	// Get the "city" member 
	if (doc.HasMember("city") && doc["city"].IsString()) { 
		std::string city = doc["city"].GetString(); 
		std::cout << "City: " << city << std::endl; 
	} 

	// Get the "skills" array 
	if (doc.HasMember("skills") 
		&& doc["skills"].IsArray()) { 
		const rapidjson::Value& skills = doc["skills"]; 
		std::cout << "Skills: "; 
		for (rapidjson::SizeType i = 0; i < skills.Size(); 
			i++) { 
			if (skills[i].IsString()) { 
				std::string skill = skills[i].GetString(); 
				std::cout << skill << " "; 
			} 
		} 
		std::cout << std::endl; 
	} 

	return 0; 
}
