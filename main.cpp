#include <iostream>
#include "indexador.h"

int main() {
    Indexador indexador;
    std::string pasta_documentos = "./documentos";
    indexador.construirIndice(pasta_documentos);

    std::string consulta;
    std::cout << "Digite a palavra para consulta: ";
    std::getline(std::cin, consulta);

    std::vector<std::string> documentos_recuperados = indexador.recuperarDocumentos(consulta);

    std::cout << "Documentos relevantes:" << std::endl;
    for (const auto& documento : documentos_recuperados) {
        std::cout << documento << std::endl;
    }

    return 0;
}