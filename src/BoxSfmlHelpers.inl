template <typename T>
b2Vec2 ConvSfToB2Vec(const sf::Vector2<T>& sfVec, int  ySize, float PPM)
{
    return {sfVec.x / PPM, (ySize - sfVec.y) / PPM};
}

sf::Vector2f ConvB2VecToSff(const b2Vec2& b2Vec, int ySize, float PPM)
{
    return {b2Vec.x * PPM, ySize - b2Vec.y * PPM};
}

sf::Vector2i ConvB2VecToSfi(const b2Vec2& b2Vec, int ySize, float PPM)
{
    return {static_cast<int>(b2Vec.x * PPM),
            static_cast<int>(ySize - b2Vec.y * PPM)};
}
