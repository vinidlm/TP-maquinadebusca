#include "indexador.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

std::string Indexador::normalizarPalavra(const std::string& palavra) {
    std::string palavra_normalizada;
    for (char c : palavra) {
        if (isalpha(c)) {
            palavra_normalizada += tolower(c);
        }
    }
    return palavra_normalizada;
}

void Indexador::construirIndice(const std::string& pasta_documentos) {
    for (const auto& entry : fs::directory_iterator(pasta_documentos)) {
        if (entry.is_regular_file()) {
            std::string nome_arquivo = entry.path().filename().string();
            std::ifstream arquivo_leitura(entry.path().string());

            std::string linha, palavra;
            std::map<std::string, int> documentos_ocorrencia;

            while (std::getline(arquivo_leitura, linha)) {
                std::stringstream stream(linha);

                while (stream >> palavra) {
                    std::string palavra_normalizada = normalizarPalavra(palavra);
                    documentos_ocorrencia[palavra_normalizada]++;
                }
            }

            for (const auto& ocorrencia : documentos_ocorrencia) {
                indice_invertido[ocorrencia.first][nome_arquivo] = ocorrencia.second;
            }
        }
    }
}

std::vector<std::string> Indexador::recuperarDocumentos(const std::string& consulta) {
    std::stringstream stream(consulta);
    std::string palavra;
    std::vector<std::string> palavras_consulta;
    std::map<std::string, int> documentos_ocorrencia;
    std::vector<std::pair<int, std::string>> documentos_ordenados;

    while (stream >> palavra) {
        palavras_consulta.push_back(normalizarPalavra(palavra));
    }

    for (const auto& palavra : palavras_consulta) {
        const auto& documentos = indice_invertido[palavra];
        for (const auto& documento : documentos) {
            documentos_ocorrencia[documento.first] += documento.second;
        }
    }

    for (const auto& documento : documentos_ocorrencia) {
        documentos_ordenados.emplace_back(documento.second, documento.first);
    }
    std::sort(documentos_ordenados.rbegin(), documentos_ordenados.rend());

    std::vector<std::string> documentos_ordenados_final;
    for (const auto& documento : documentos_ordenados) {
        documentos_ordenados_final.push_back(documento.second);
    }
    return documentos_ordenados_final;
}