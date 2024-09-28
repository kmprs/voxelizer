#pragma once

#include "reader.hpp"


class OBJReader : public Reader
{
public:
    OBJReader() = default;
    [[nodiscard]] std::vector<std::shared_ptr<TriangleFace>> read(const std::string &path) const override;
};