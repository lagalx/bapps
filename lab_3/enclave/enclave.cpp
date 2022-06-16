#include "enclave_t.h"
#include <string.h>
#include "sgx_trts.h"

//данные в виде таблицы, которые необходимо защитить
const char table[6][41] = {
    "UG4TKHQYDHW0J1DOXJU0JRUPW0CQVX8LPL72FCAS",
    "U3TB54FIFZH7W7IRPJVFSKKRM142EDE583EYCQWA",
    "E3545RH8OZGUTN9222O4J831OYRQPXUSUB3BTIOW",
    "15BOQ0IQFKGVUQ2IUUN2LNCOU247P2BKYQ53VAX4",
    "0E8ZSELC1DA9ZMZT63I3DG78MA3B6NEPE770GAS7"
};

//функция для запроса к таблице
void foo(char* buf, size_t len, size_t idx) {
    if (idx < 5) {
        const char* data_ptr = data_ptr = table[idx];
        memcpy(buf, data_ptr, strlen(data_ptr + 1));
    }
    else {
        memset(buf, 0, strlen(table[0])); //возврат нулевой строки, если индекс в таблице не найден
    }
    return;
}
