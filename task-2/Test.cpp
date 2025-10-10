#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/istreamwrapper.h>
// using namespace std;
namespace rj = rapidjson;

class OpenFrameByMovieID{
  private:
    std::string VARIABLE_PATHXL;
    
  public:
    OpenFrameByMovieID(std::string pathXL){
      VARIABLE_PATHXL = pathXL;
    }
    rj::Document OpenDocument(std::string m){
      // std::ostringstream oss;
      // oss << m;
      std::string path_json = VARIABLE_PATHXL + "/" + m;
      rj::Document doc;

      std::ifstream ifs(path_json);
      if(!ifs.is_open()){
        std::cout <<"error opening file" << std::endl;
        doc.SetNull();
        return doc;
      }
      rj::IStreamWrapper isw(ifs);

      doc.ParseStream(isw);
      if(doc.HasParseError()){
        std::cout << "JSON Parse error" << std::endl;
        doc.SetNull();
        return doc;
      }
      return doc;
    }
};

int main(){
  std::cout << "Input variable M: ";
  std::string m; std::cin >> m;
  OpenFrameByMovieID Worker("../../XL");
  // opem motion_movie
  rj::Document motion_movie_doc = Worker.OpenDocument("motion_movie/" + m + ".json");
  if (motion_movie_doc.IsNull()) {
    return 1;
  }

  const rj::Value& motion_unit = motion_movie_doc["motion_unit"];  // array
  if (!motion_unit.IsArray() || motion_unit.Empty()) {
    std::cout << "motion_unit kosong atau bukan array!" << std::endl;
    return 1;
  }
  
  const rj::Value& first_unit = motion_unit[0];  // ambil elemen pertama
  if (!first_unit.IsObject()) {
    std::cout << "elemen pertama motion_unit bukan object!" << std::endl;
    return 1;
  }
  int motion_unit_id;
  if (first_unit.HasMember("id") && first_unit["id"].IsInt()) {
    motion_unit_id = first_unit["id"].GetInt();
    std::cout << "Motion_unit ID =" << motion_unit_id << std::endl;
  } else {
    std::cout << "field 'id' tidak ditemukan atau bukan integer!" << std::endl;
    return 1;
  }
  std::ostringstream oss;
  oss << motion_unit_id;
  rj::Document motion_unit_doc = Worker.OpenDocument("motion_unit/" + oss.str() + ".json");
  if (motion_unit_doc.IsNull()) {
    return 1;
  }
  rj::Value& motion_frame = motion_unit_doc["motion_frame"];
  if (!motion_frame.IsArray() || motion_frame.Empty()) {
    std::cout << "motion_unit kosong atau bukan array!" << std::endl;
    return 1;
  }
  std::cout << "-- motion_frame --" << std::endl;
  for (size_t i = 0; i < motion_frame.Size(); i++) {
    const rj::Value& row = motion_frame[i];
    if (row.IsArray()) {
      for (size_t j = 0; j < row.Size(); j++) {
        std::cout << row[j].GetInt() << " ";
      }
      std::cout << std::endl;
    }
  }
  return 0;
}