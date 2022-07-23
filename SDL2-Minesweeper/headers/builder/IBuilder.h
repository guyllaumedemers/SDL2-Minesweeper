/// <summary>
/// base class for builder pattern, use to work around generic implementation in its derived child
/// </summary>
#ifndef INCLUDED_IBUILDER
#define INCLUDED_IBUILDER

namespace Toolset {
    class IBuilder {
    protected:
        IBuilder() = default;
    public:
        IBuilder(const IBuilder&) = delete;
        IBuilder(IBuilder&&) = delete;
        virtual ~IBuilder() = 0;
        IBuilder& operator=(const IBuilder&) = delete;
        IBuilder& operator=(IBuilder&&) = delete;
    };

    inline IBuilder::~IBuilder()
    {}
}
#endif