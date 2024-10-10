#include <rtkcommon/utils/DCMReader.h>

#include "StoreInDatabase.h"
#include "Study.h"
#include "Patient.h"
#include "Series.h"
#include "Image.h"
#include "Statement.h"

using namespace rtkplanning;

StoreInDatabase::StoreInDatabase()
{
    logger_planning = spdlog::get("rtkplanning");
}

long long StoreInDatabase::StorePatientInDb(dict_type dictionary) const
{
    long long patient_UID = 0;
    try
    {
        auto patient_ID = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagPatientID);
        auto patient_exists = Patient::get(patient_ID);
        if (!patient_exists)
        {
            auto patient = std::make_shared<Patient>();
            patient->PatientID           = patient_ID;
            patient->PatientName         = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagPatientName);
            patient->PatientBirthDate    = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagPatientBirthDate);
            patient->PatientBirthTime    = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagPatientBirthTime);
            patient->PatientSex          = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagPatientSex);
            patient->PatientAge          = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagPatientAge);

            if (Patient::insert(*patient))
                patient_UID = Patient::getLastInsertedUID();
            // else
            //     patient_UID = Patient::get(patient->PatientID)->UID;
        }
        else
            patient_UID = Patient::get(patient_exists->PatientID)->UID;
    }
    catch (const std::exception& e)
    {
        SPDLOG_LOGGER_ERROR(logger_planning, "Exception while storing patient data into database: {}!", e.what());
    }

    return patient_UID;
}

void StoreInDatabase::StoreStudyInDb(dict_type dictionary, long long patient_UID) const
{
    try
    {
        auto study_ID = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagStudyID);
        auto study_existing = Study::getByStudyId(study_ID.value());
        if (!study_existing || (study_existing->PatientUID != patient_UID))
        {
            auto study = std::make_shared<Study>();
            study->StudyInstanceUID      = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagStudyInstanceUID).value();
            study->StudyID               = study_ID;
            study->StudyDate             = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagStudyDate);
            study->StudyTime             = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagStudyTime);
            study->StudyDescription      = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagStudyDescription);
            study->AccessionNumber       = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagAccessionNumber);
            study->PatientUID            = patient_UID;

            SPDLOG_LOGGER_INFO(logger_planning, "Study with StudyInstanceUID {} doesn't exist in database.", study->StudyInstanceUID);
            Study::insert(*study);
        }
    }
    catch (const std::exception& e)
    {
        SPDLOG_LOGGER_ERROR(logger_planning, "Exception while storing study data into database: {}!", e.what());
    }
}

void StoreInDatabase::StoreSeriesInDb(dict_type dictionary, std::string series_inst_UID_value) const
{
    try
    {
        // If series already exists in database, skip inserting
        if (!Series::get(series_inst_UID_value))
        {
            auto series = std::make_shared<Series>();
            series->SeriesInstanceUID    = series_inst_UID_value;
            series->SeriesNumber         = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagSeriesNumber);
            series->SeriesDate           = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagSeriesDate);
            series->SeriesTime           = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagSeriesTime);
            series->SeriesDescription    = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagSeriesDescription);
            series->Modality             = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagModality);
            series->BodyPartExamined     = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagBodyPartExamined);
            series->StudyInstanceUID     = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagStudyInstanceUID).value();

            SPDLOG_LOGGER_INFO(logger_planning, "Series with SeriesInstanceUID {} doesn't exist in database.", series_inst_UID_value);
            Series::insert(*series);
        }
    }
    catch (const std::exception& e)
    {
        SPDLOG_LOGGER_ERROR(logger_planning, "Exception while storing series into database: {}!", e.what());
    }
}

void StoreInDatabase::StoreImageInDb(dict_type dictionary, const std::filesystem::path& file_path) const
{
    auto sop_instance_UID = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagSOPInstanceUID);
    auto series_inst_UID = rtkcommon::DCMReader::getTagValue(dictionary, rtkcommon::DCMReader::tagSeriesInstanceUID);

    try
    {
        Image image;
        image.SOPInstanceUID        = sop_instance_UID.value();
        image.Filename              = file_path.string();
        image.SeriesInstanceUID     = series_inst_UID.value();

        Image::insert(image);
    }
    catch (const std::exception& e)
    {
        SPDLOG_LOGGER_ERROR(logger_planning, "Exception while storing image {} into database: {}!", file_path.string(), e.what());
    }
}
