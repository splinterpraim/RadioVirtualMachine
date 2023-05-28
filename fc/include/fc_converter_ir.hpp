/**
 * @file fc_converter_ir.hpp
 * @author Elena Potapova (krylelena99@yandex.ru)
 * @brief Class-converter to RVM IR
 * @version 0.2
 * @copyright Copyright (c) 2023
 */

#ifndef FC_CONVERTER_IR_CLASS
#define FC_CONVERTER_IR_CLASS
#include <string>

#include "ir_objects.hpp"
#include "config_code_structure.hpp"

class fc_ConverterIR
{
public:
    /**
     * @brief Converts from Ir Objects to RVM IR (config structs)
     *
     * @param[in] irObjects IR Objects
     *
     * @retval ConfigObjects Config Objects
     */
    ConfigObjects convert(IrObjects &irObjects);

    /**
     * @brief Sets the Id Map File 
     *
     * @param[in] fileName File name of id mapping file
     */
    void setIdMapFile(const std::string &fileName);

    /**
     * @brief Sets the Id Map File 
     */
    std::string getIdMapFile() const;

private:
    std::string idMapFile;
    /**
     * @brief Fills fields of Control Section for Config code objects
     *
     * @param[in] configObjects Config code objects
     * @param[in] irObjects IR objects
     */
    void fillControlSection(ConfigObjects &configObjects, IrObjects &irObjects);

    /**
     * @brief Fills fields of DO Section for Config code objects
     *
     * @param[in] configObjects Config code objects
     * @param[in] irObjects IR objects
     */
    void fillDoSection(ConfigObjects &configObjects, IrObjects &irObjects);

    /**
     * @brief Creates the DO Configs from IR objects
     *
     * @param[in] irObjects IR objects
     *
     * @retval DO_Config* Pointer to created DO Configs
     */
    DO_Config *getDoConfig(IrObjects &irObjects);

    /**
     * @brief Gets data size from IR data for the DO Config field
     *
     * @param[in] irData IR data
     *
     * @retval uint32_t Data size
     */
    uint32_t getDoConfig_size(IrData &irData);

    /**
     * @brief Gets real data length from IR data for the DO Config field
     *
     * @param[in] irData IR data
     * @param[in] size Data size
     *
     * @retval uint8_t Data length
     */
    uint8_t getDoConfig_length(IrData &irData, uint32_t size);

    /**
     * @brief Gets size of data depending on type
     *
     * @param[in] dataVal Data value
     * @param[in] dataType Type of data
     *
     * @retval uint8_t Size of data
     */
    uint8_t detectSize(std::string dataVal, int dataType);

    /**
     * @brief Gets the file length
     *
     * @param[in] fileName Name of file
     *
     * @retval size_t File length
     */
    size_t getFileLen(std::string fileName);

    /**
     * @brief Gets data from IR data for the DO Config field
     *
     * @param[in] irData IR data
     * @param[in] len Data length
     *
     * @retval uint8_t* Pointer to data
     */
    uint8_t *getDoConfig_data(IrData &irData, uint8_t len);

    /**
     * @brief Gets the file data
     *
     * @param[in] fileName Name of file
     *
     * @retval uint8_t* Pointer to data from file
     */
    uint8_t *getFileData(std::string fileName);

    /**
     * @brief Creates the ASF Configs from IR objects
     *
     * @param[in] irObjects IR objects
     *
     * @retval ASF_Config* Pointer to created ASF Configs
     */
    ASF_Config *getAsfConfig(IrObjects &irObjects);

    /**
     * @brief Gets amount of IR data connections with IR operators for the AsfConfig field
     *
     * @param[in] irData IR data
     * @param[in] irObjects IR objects
     *
     * @retval uint8_t Amount of IR data connections
     */
    uint8_t getAsfConfig_numApe(IrData &irData, IrObjects &irObjects);

    /**
     * @brief Gets IR data connections with IR operators for the AsfConfig field
     *
     * @param[in] irData    IR data
     * @param[in] N         Amount of IR data connections
     * @param[in] irObjects IR objects
     *
     * @retval ASF_variable_part* Pointer to IR data connections
     */
    ASF_variable_part *getAsfConfig_APE_KP(IrData &irData, uint8_t N, IrObjects &irObjects);

    /**
     * @brief Gets operator ID in context of Config Code
     *
     * @param[in] apeId IR operator ID
     * @param[in] irObjects IR objects
     *
     * @retval uint8_t Operator ID
     */
    uint8_t getApeIdForCfgCode(std::string apeId, std::vector<IrOperator> &operators);

    /**
     * @brief Gets the amount of input links in operator
     *
     * @param[in] opId IR operator ID
     * @param[in] links Vector of IR links
     *
     * @retval int Amount of input links
     */
    uint8_t getNumInputLink(std::string opId, std::vector<IrLink> &links);

    /**
     * @brief Fills fields of APE Section for Config code objects
     *
     * @param[in] configObjects Config code objects
     * @param[in] irObjects IR objects
     */
    void fillApeSection(ConfigObjects &configObjects, IrObjects &irObjects);

    /**
     * @brief Creates the APE Configs from IR objects
     *
     * @param[in] irObjects IR objects
     *
     * @retval APE_Config* Pointer to APE Configs
     */
    APE_Config *getApeConfig(IrObjects &irObjects);

    /**
     * @brief Checks the mismatch between the number of input/output ports of the operator in radiolib
     *
     * @param[in] irOperator IR operator
     * @param[in] irObjects IR objects
     *
     * @retval true Input/output ports are matched
     * @retval false Input/output ports don't match
     */
    bool checkNumPortsInRadioLib(IrOperator &irOperator, IrObjects &irObjects);

    /**
     * @brief Gets the number of data connections from APE
     *
     * @param[in] opId IR operator ID
     * @param[in] irObjects IR objects
     *
     * @retval uint8_t Number of data connections
     */
    uint8_t getApeNumPorts(std::string opId, IrObjects &irObjects);

    /**
     * @brief Gets the amount of output links in operator
     *
     * @param[in] opId IR operator ID
     * @param[in] links Vector of IR links
     *
     * @retval uint8_t Amount of output links
     */
    uint8_t getNumOutputLink(std::string opId, std::vector<IrLink> &links);

    /**
     * @brief Creates the Access Type for ports of operator
     *
     * @param[in] apeNumPorts   Number of data connections
     * @param[in] opId          IR operator ID
     * @param[in] irObjects     IR objects
     *
     * @retval uint8_t* Pointer to Access Type for ports
     */
    uint8_t *getAccessType(uint8_t apeNumPorts, std::string opId, IrObjects &irObjects);

    /**
     * @brief Generates file with id-name maps
     *
     * @param[in] operators Vector of IR operators
     */
    void generateIdMapFile(std::vector<IrOperator> &operators);
};

#endif // FC_CONVERTER_IR_CLASS
