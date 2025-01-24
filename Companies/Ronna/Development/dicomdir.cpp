#include "gdcmReader.h"
#include "gdcmSequenceOfItems.h"

//* DICOM reader
gdcm::Reader reader; // "gdcmReader.h"
reader.SetFileName(dcmdir_file.c_str());

if (!reader.Read()) {
    std::cerr << "Error reading DICOMDIR file" << std::endl;
}

gdcm::DataSet &dataset = reader.GetFile().GetDataSet();

gdcm::DataSet::ConstIterator iter = dataset.Begin();
while (iter != dataset.End())
{
    const gdcm::DataElement &dataElement = *iter;
    const gdcm::Tag &tag = dataElement.GetTag(); // gdcmDataElement.h
    std::cout << "Tag: " << tag << ", Value: " << dataElement.GetValue() << std::endl;
    ++iter;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


auto nameGenerator = itk::GDCMSeriesFileNames::New();
// nameGenerator->SetUseSeriesDetails(true);
// nameGenerator->AddSeriesRestriction("0008|0021");
// nameGenerator->SetGlobalWarningDisplay(false);
std::cout << dcmdir_file.parent_path().string() << std::endl;
auto dcmdir_parent = dcmdir_file.parent_path();
auto dcmdir_parent_it = std::filesystem::directory_iterator(dcmdir_parent);

nameGenerator->SetDirectory(dcmdir_file.parent_path().string());

const std::vector<std::string>& seriesUIDs = nameGenerator->GetSeriesUIDs();
for (auto &seriesUID : seriesUIDs) {
    // Output the series description
    std::cout << "Series UID: " << seriesUID << std::endl;
    // Get the file names for the series
    const std::vector<std::string> &fileNames = nameGenerator->GetFileNames(seriesUID);
}
// itk::MetaDataDictionary dictionary = GetDcmMetaData(dcmdir);
