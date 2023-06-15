#ifndef INDEXADOR_H
#define INDEXADOR_H

#include <map>
#include <string>
#include <vector>

class Indexador {
private:
    std::map<std::string, std::map<std::string, int>> indice_invertido;

    std::string normalizarPalavra(const std::string& palavra);

public:
    void construirIndice(const std::string& pasta_documentos);
    std::vector<std::string> recuperarDocumentos(const std::string& consulta);
};

#endif // INDEXADOR_H