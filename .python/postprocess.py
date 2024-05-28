import re

def regex_variants(content: str, oldvalue, newvalue):
    content = re.sub(oldvalue, newvalue, content)
    return content

def replace_variants(content: str, oldvalue, newvalue):
    content = content.replace(f'-> "{oldvalue}"', f'-> "{newvalue}"')
    content = content.replace(f'-> "{oldvalue} &&"', f'-> "{newvalue}"')
    content = content.replace(f'-> "{oldvalue} &"', f'-> "{newvalue}"')
    content = content.replace(f'-> "{oldvalue} *"', f'-> "{newvalue}"')
    content = content.replace(f'-> "{oldvalue} const"', f'-> "{newvalue}"')
    content = content.replace(f'-> "{oldvalue} const &"', f'-> "{newvalue}"')

    content = content.replace(f'"{oldvalue}"', newvalue)
    content = content.replace(f'"{oldvalue} &&"', newvalue)
    content = content.replace(f'"{oldvalue} &"', newvalue)
    content = content.replace(f'"{oldvalue} *"', newvalue)
    content = content.replace(f'"{oldvalue} const"', newvalue)
    content = content.replace(f'"{oldvalue} const &"', newvalue)
    return content


def generate_enums(content: str):
    # return content
    content = content.splitlines()

    enums = {}

    last = 0
    ename = None
    lname = None
    for idx, line in enumerate(content):
         match = re.match(r"(\s*)([0-9a-zA-Z]+)([_\.])([0-9a-zA-Z_]+) = (_.+)", line)
         if match:
            spaces, name, dot, item, expr = match.groups()
            if 'value_size' in expr:
                continue

            if name.upper() != name:
                diff = idx - last
                last = idx
                if diff > 1 or name != lname:
                    lname = name
                    ename = f"{name}.{idx}"
                    print(ename)

                entry = enums.setdefault(ename, {})
                entry[item] = (spaces, idx, expr, dot == '.')

    for entry, values in enums.items():
        first = True
        klass = entry.split('.')[0]
        cls = ["IntEnum", "IntFlag"]["flag" in klass.lower() or "capability" in klass.lower()]
        for value, (spaces, lno, expr, isdot) in values.items():
            posacc = "" if not isdot else ".getValue()"
            if first:
                first = False
                content[lno] = f"\n{spaces}class {klass}Defs({cls}):\n{spaces}    {value} = {expr}{posacc}"
            else:
                content[lno] = f"{spaces}    {value} = {expr}{posacc}"

    return '\n'.join(content)


def modify(path_to_file: str, cls):
    # ------------------------
    # Read in the whole file
    # ------------------------
    with open(path_to_file, 'r') as file:
        file_contents = file.read()

    file_contents = file_contents.replace('import la_networkInterfaceHelper', '')
    file_contents = file_contents.replace('import avdeccEntityModel', '')
    file_contents = file_contents.replace('import la_networkInterfaceHelper', '')
    
    file_contents = file_contents.replace("from sys import version_info as _swig_python_version_info", f"from enum import IntEnum, IntFlag\n{cls.inject_import()}")

    # ------------------------
    # Perform find and replace
    # ------------------------

    # c++ orphans
    file_contents = regex_variants(file_contents, r',std::allocator<[^>]*>', '')
    file_contents = regex_variants(file_contents, r',std::less<[^>]*>', '')
    file_contents = file_contents.replace(r',la::avdecc::utils::EnumClassHash', '')

    # avdecc list and array deduction

    file_contents = regex_variants(file_contents, r'std::vector<[^>]*>::iterator', '')
    file_contents = regex_variants(file_contents, r'std::vector<[^>]*>::reverse_iterator', '')
    file_contents = regex_variants(file_contents, r'std::vector<[^>]*>::allocator_type', '')
    file_contents = regex_variants(file_contents, r'std::vector<[^>]*> \*', '')

    file_contents = regex_variants(file_contents, r'std::vector<[^>]*>::difference_type', 'size_t')
    file_contents = regex_variants(file_contents, r'std::vector<[^>]*>::size_type', 'size_t')
    file_contents = regex_variants(file_contents, r'std::vector< ([^>]*) >::value_type', r'\g<1>')


    file_contents = regex_variants(file_contents, r'std::array<[^>]*>::iterator', '')
    file_contents = regex_variants(file_contents, r'std::array<[^>]*>::reverse_iterator', '')
    file_contents = regex_variants(file_contents, r'std::array<[^>]*>::allocator_type', '')
    file_contents = regex_variants(file_contents, r'std::array<[^>]*> \*', '')

    file_contents = regex_variants(file_contents, r'std::array<[^>]*>::difference_type', 'size_t')
    file_contents = regex_variants(file_contents, r'std::array<[^>]*>::size_type', 'size_t')
    file_contents = regex_variants(file_contents, r'std::array< ([^,]*),[^>]* >::value_type', r'\g<1>')

    file_contents = regex_variants(file_contents, r'std::set<[^>]*>::iterator', '')
    file_contents = regex_variants(file_contents, r'std::set<[^>]*>::reverse_iterator', '')
    file_contents = regex_variants(file_contents, r'std::set<[^>]*>::difference_type', 'size_t')
    file_contents = regex_variants(file_contents, r'std::set<[^>]*>::size_type', 'size_t')
    file_contents = regex_variants(file_contents, r'std::set< ([^>]*) >::key_type( const)?( &)?', r'\g<1>')
    file_contents = regex_variants(file_contents, r'std::set< ([^>]*) >::value_type', r'\g<1>')

    file_contents = regex_variants(file_contents, r'std::map< ([^,]*),([^>]*) >::iterator', '')
    file_contents = regex_variants(file_contents, r'std::map< ([^,]*),([^>]*) >::reverse_iterator', '')
    file_contents = regex_variants(file_contents, r'std::map< ([^,]*),([^>]*) >::size_type', 'size_t')
    file_contents = regex_variants(file_contents, r'std::map< ([^,]*),([^>]*) >::difference_type', 'size_t')
    file_contents = regex_variants(file_contents, r'std::map< ([^,]*),([^>]*) >::key_type( const)?( &)?', r'\g<1>')
    file_contents = regex_variants(file_contents, r'std::map< ([^,]*),([^>]*) >::mapped_type( const)?( &)?', r'\g<2>')

    file_contents = regex_variants(file_contents, r'std::unordered_map< ([^,]*),([^>]*) >::iterator( \*)?', '')
    file_contents = regex_variants(file_contents, r'std::unordered_map< ([^,]*),([^>]*) >::reverse_iterator', '')
    file_contents = regex_variants(file_contents, r'std::unordered_map< ([^,]*),([^>]*) >::size_type', 'size_t')
    file_contents = regex_variants(file_contents, r'std::unordered_map< (enum )?([^,]*),([^>]*) >::key_type( const)?( &)?', r'\g<2>')
    file_contents = regex_variants(file_contents, r'std::unordered_map< ([^,]*),([^>]*) >::mapped_type( const)?( &)?', r'\g<2>')

    # lists and sets
    file_contents = regex_variants(file_contents, r'std::unique_ptr< ([^>]*) >', r'\g<1>')
    file_contents = regex_variants(file_contents, r'std::vector< ([^>]*) >', r'List[\g<1>]')
    file_contents = regex_variants(file_contents, r'std::set< ([^>]*) >', r'Set[\g<1>]')
    file_contents = regex_variants(file_contents, r'std::optional< ([^>]*) >', r'Optional[\g<1>]')
    file_contents = regex_variants(file_contents, r'std::map< ([^,]*),([^>]*) >', r'Dict[\g<1>, \g<2>]')
    file_contents = regex_variants(file_contents, r'std::unordered_map< ([^,]*),([^>]*) >', r'Dict[\g<1>, \g<2>]')

    # avdecc enum bitfield
    file_contents = regex_variants(file_contents, r'utils::EnumBitfield<[^>]*>::difference_type( const)?( &)?', 'size_t')
    file_contents = regex_variants(file_contents, r'utils::EnumBitfield< enum ([^>]*) >::value_type', r'\g<1>')
    file_contents = regex_variants(file_contents, r'utils::EnumBitfield< ([^>]*) >::underlying_value_type', r'int')
    file_contents = regex_variants(file_contents, r'utils::EnumBitfield<[^>]*>( const)?( &)?', '')

    # avdecc typed define
    file_contents = regex_variants(file_contents, r'utils::TypedDefine< ([^,]*),[^>]* >::value_type', r'\g<1>')


    # base types
    file_contents = replace_variants(file_contents, 'void', 'None')

    file_contents = replace_variants(file_contents, 'bool', 'bool')

    file_contents = replace_variants(file_contents, 'std::string', 'str')
    file_contents = replace_variants(file_contents, 'char const *', 'str')

    file_contents = replace_variants(file_contents, 'size_t', 'int')

    file_contents = replace_variants(file_contents, 'std::uint8_t', 'UInt8')
    file_contents = replace_variants(file_contents, 'std::uint16_t', 'UInt16')
    file_contents = replace_variants(file_contents, 'std::uint32_t', 'UInt32')
    file_contents = replace_variants(file_contents, 'std::uint64_t', 'UInt64')

    file_contents = replace_variants(file_contents, 'std::int8_t', 'Int8')
    file_contents = replace_variants(file_contents, 'std::int16_t', 'Int16')
    file_contents = replace_variants(file_contents, 'std::int32_t', 'Int32')
    file_contents = replace_variants(file_contents, 'std::int64_t', 'Int64')

    file_contents = replace_variants(file_contents, 'unsigned char', 'Char')
    file_contents = replace_variants(file_contents, 'unsigned short', 'UInt16')
    file_contents = replace_variants(file_contents, 'unsigned int', 'UInt32')
    file_contents = replace_variants(file_contents, 'long long', 'Int64')
    file_contents = replace_variants(file_contents, 'double', 'float')
    file_contents = replace_variants(file_contents, 'ptrdiff_t', 'int')


    # avdecc namespace
    file_contents = cls.patch_namespace(file_contents)


    # tuples
    file_contents = replace_variants(file_contents, 'std::pair< std::uint8_t,std::uint32_t >', 'Tuple[UInt8, UInt8]')
    file_contents = replace_variants(file_contents, 'std::pair< std::uint16_t,std::uint8_t >', 'Tuple[UInt16, UInt8]')
    file_contents = replace_variants(file_contents, 'std::pair< std::int8_t,ControlValueUnit::Unit >', 'Tuple[Int8, ControlValueUnit_Unit]')

    file_contents = replace_variants(file_contents, 'std::array< AvdeccFixedString,7 >', 'List[AvdeccFixedString]')
    
    file_contents = replace_variants(file_contents, 'std::span< uint8_t const >', 'bytes')

    # cleanup orphans
    file_contents = file_contents.replace(': ""', '')
    file_contents = file_contents.replace(' -> "":', ':')
    file_contents = file_contents.replace(' -> "std::pair< , >":', ':')
    file_contents = file_contents.replace(' -> "std::pair< ,bool >":', ':')

    file_contents = file_contents.replace(' -> "swig::SwigPyIterator *":', ':')
    file_contents = file_contents.replace(' -> "swig::SwigPyIterator &":', ':')
    file_contents = file_contents.replace(' -> "PyObject *":', ':')
    file_contents = file_contents.replace('] >"', ']"')


    file_contents = file_contents.replace('std::uint8_t', 'UInt8')
    file_contents = file_contents.replace('std::uint16_t', 'UInt16')
    file_contents = file_contents.replace('std::uint32_t', 'UInt32')
    file_contents = file_contents.replace('std::uint64_t', 'UInt64')

    file_contents = file_contents.replace('std::int8_t', 'Int8')
    file_contents = file_contents.replace('std::int16_t', 'Int16')
    file_contents = file_contents.replace('std::int32_t', 'Int32')
    file_contents = file_contents.replace('std::int64_t', 'Int64')

    # process enums
    file_contents = generate_enums(file_contents)
    
    file_contents = file_contents.replace('_GlobalAvbInterfaceIndex.getValue()', '_GlobalAvbInterfaceIndex') # avdecc fix

    # ------------------------
    # Save the changes back to the file
    # ------------------------
    with open(path_to_file, 'w') as file:
        file.write(file_contents)



class InterfaceHelperPatcher:
    @staticmethod
    def inject_import() -> str:
        return """
if __package__ or "." in __name__:
    from .avdeccTypes import *
else:
    from avdeccTypes import *
"""

    @staticmethod
    def patch_namespace(file_contents: str) -> str:
        file_contents = regex_variants(file_contents, r'la::networkInterface::Interface::([^\s]+)( const)?( &)?', r'\g<1>')
        file_contents = replace_variants(file_contents, 'Type', 'Interface_Type')

        file_contents = regex_variants(file_contents, r'la::networkInterface::([^\s]+)( const)?( &)?', r'\g<1>')
        file_contents = replace_variants(file_contents, 'IPAddress::value_type_v4', 'Tuple[UInt8, UInt8, UInt8, UInt8]')
        file_contents = replace_variants(file_contents, 'IPAddress::value_type_v6', 'Tuple[UInt16, UInt16, UInt16, UInt16, UInt16, UInt16, UInt16, UInt16]')
        file_contents = replace_variants(file_contents, 'IPAddress::value_type_packed_v4', 'UInt32')
        file_contents = replace_variants(file_contents, 'IPAddress::Type', 'Address_Type')

        return file_contents

modify("la_networkInterfaceHelper.py", InterfaceHelperPatcher)



class EntityModelPatcher:
    @staticmethod
    def inject_import() -> str:
        return """
if __package__ or "." in __name__:
    from .avdeccTypes import *
    from . import la_networkInterfaceHelper as nih
else:
    from avdeccTypes import *
    import la_networkInterfaceHelper as nih
"""

    @staticmethod
    def patch_namespace(file_contents: str) -> str:
        file_contents = regex_variants(file_contents, r'la::avdecc::entity::model::([^\s]+)( const)?( &)?', r'\g<1>')
        file_contents = regex_variants(file_contents, r'la::avdecc::entity::([^\s]+)( const)?( &)?', r'\g<1>')
        file_contents = regex_variants(file_contents, r'la::avdecc::protocol::([^\s]+)( const)?( &)?', r'\g<1>')
        file_contents = regex_variants(file_contents, r'la::avdecc::([^\s]+)( const)?( &)?', r'\g<1>')

        file_contents = replace_variants(file_contents, 'UniqueIdentifier::value_type', 'UInt64')
        file_contents = replace_variants(file_contents, 'SamplingRate::value_type', 'UInt32')
        file_contents = replace_variants(file_contents, 'StreamFormat::value_type', 'UInt64')
        file_contents = replace_variants(file_contents, 'ControlValueUnit::value_type', 'UInt16')
        file_contents = replace_variants(file_contents, 'ControlValueUnit::Unit', 'ControlValueUnit_Unit')
        file_contents = replace_variants(file_contents, 'ControlValueType::value_type', 'UInt16')
        file_contents = replace_variants(file_contents, 'ControlValueType::Type', 'ControlValueType_Type')
        file_contents = replace_variants(file_contents, 'LocalizedStringReference::value_type', 'UInt16')

        file_contents = replace_variants(file_contents, 'AudioMappings', 'AudioMappingVector')
        file_contents = replace_variants(file_contents, 'MsrpMappings', 'MsrpMappingVector')
        file_contents = replace_variants(file_contents, 'PathSequence', 'UniqueIdentifierVector')

        # process nih namespace
        file_contents = regex_variants(file_contents, r'la::networkInterface::([^\s]+)( const)?( &)?', r'nih.\g<1>')

        return file_contents

modify("avdeccEntityModel.py", EntityModelPatcher)



class AvdeccPatcher:
    @staticmethod
    def inject_import() -> str:
        return """
if __package__ or "." in __name__:
    from .avdeccTypes import *
    from . import la_networkInterfaceHelper as nih
    from . import avdeccEntityModel as avem
else:
    from avdeccTypes import *
    import la_networkInterfaceHelper as nih
    import avdeccEntityModel as avem
"""

    @staticmethod
    def patch_namespace(file_contents: str) -> str:
        file_contents = replace_variants(file_contents, 'la::avdecc::ExecutorManager::ExecutorWrapper', 'ExecutorWrapper')
        file_contents = replace_variants(file_contents, 'la::avdecc::ExecutorManager', 'ExecutorManager')
        file_contents = replace_variants(file_contents, 'la::avdecc::Executor', 'Executor')
        file_contents = replace_variants(file_contents, 'la::avdecc::EndStation', 'EndStation')
        file_contents = replace_variants(file_contents, 'la::avdecc::entity::ControllerEntity', 'ControllerEntity')

        file_contents = regex_variants(file_contents, r'la::avdecc::entity::LocalEntity::([^\s]+)( const)?( &)?', r'\g<1>')
        file_contents = regex_variants(file_contents, r'la::avdecc::entity::Entity::([^\s]+)( const)?( &)?', r'\g<1>')
        file_contents = regex_variants(file_contents, r'la::avdecc::protocol::([^\s]+)( const)?( &)?', r'\g<1>')

        # process avem namespace
        file_contents = regex_variants(file_contents, r'la::avdecc::entity::model::([^\s]+)( const)?( &)?', r'avem.\g<1>')
        file_contents = regex_variants(file_contents, r'la::avdecc::entity::([^\s]+)( const)?( &)?', r'avem.\g<1>')

        file_contents = regex_variants(file_contents, 'la::avdecc::UniqueIdentifier( const)?( &)?', 'avem.UniqueIdentifier')
        file_contents = replace_variants(file_contents, 'Tlvs', 'avem.Tlvs')
        file_contents = replace_variants(file_contents, 'AsPath', 'avem.AsPath')
        file_contents = replace_variants(file_contents, 'AcmpStatus', 'avem.AcmpStatus')
        file_contents = replace_variants(file_contents, 'AudioClusterDescriptor', 'avem.AudioClusterDescriptor')
        file_contents = replace_variants(file_contents, 'AudioMapDescriptor', 'avem.AudioMapDescriptor')
        file_contents = replace_variants(file_contents, 'AudioMappingVector', 'avem.AudioMappingVector')
        file_contents = replace_variants(file_contents, 'AudioUnitDescriptor', 'avem.AudioUnitDescriptor')
        file_contents = replace_variants(file_contents, 'AvbInfo', 'avem.AvbInfo')
        file_contents = replace_variants(file_contents, 'AvbInterfaceCounterValidFlags', 'avem.DescriptorCounterArray')
        file_contents = replace_variants(file_contents, 'AvbInterfaceDescriptor', 'avem.AvbInterfaceDescriptor')
        file_contents = replace_variants(file_contents, 'AvdeccFixedString', 'avem.AvdeccFixedString')
        file_contents = replace_variants(file_contents, 'ClockDomainCounterValidFlags', 'avem.ClockDomainCounterValidFlags')
        file_contents = replace_variants(file_contents, 'ClockDomainDescriptor', 'avem.ClockDomainDescriptor')
        file_contents = replace_variants(file_contents, 'ClockSourceDescriptor', 'avem.ClockSourceDescriptor')
        file_contents = replace_variants(file_contents, 'ConfigurationDescriptor', 'avem.ConfigurationDescriptor')
        file_contents = replace_variants(file_contents, 'ConnectionFlags', 'avem.ConnectionFlags')
        file_contents = replace_variants(file_contents, 'ControlDescriptor', 'avem.ControlDescriptor')
        file_contents = replace_variants(file_contents, 'ControlValues', 'avem.ControlValues')
        file_contents = replace_variants(file_contents, 'DescriptorCounterArray', 'avem.DescriptorCounterArray')
        file_contents = replace_variants(file_contents, 'EntityCapabilities', 'avem.EntityCapabilities')
        file_contents = replace_variants(file_contents, 'EntityCounterValidFlags', 'avem.EntityCounterValidFlags')
        file_contents = replace_variants(file_contents, 'EntityDescriptor', 'avem.EntityDescriptor')
        file_contents = replace_variants(file_contents, 'ExternalPortDescriptor', 'avem.ExternalPortDescriptor')
        file_contents = replace_variants(file_contents, 'InternalPortDescriptor', 'avem.InternalPortDescriptor')
        file_contents = replace_variants(file_contents, 'JackDescriptor', 'avem.JackDescriptor')
        file_contents = replace_variants(file_contents, 'LocaleDescriptor', 'avem.LocaleDescriptor')
        file_contents = replace_variants(file_contents, 'MemoryObjectDescriptor', 'avem.MemoryObjectDescriptor')
        file_contents = replace_variants(file_contents, 'MilanInfo', 'avem.MilanInfo')
        file_contents = replace_variants(file_contents, 'PtpInstanceDescriptor', 'avem.PtpInstanceDescriptor')
        file_contents = replace_variants(file_contents, 'PtpPortDescriptor', 'avem.PtpPortDescriptor')
        file_contents = replace_variants(file_contents, 'SamplingRate', 'avem.SamplingRate')
        file_contents = replace_variants(file_contents, 'StreamDescriptor', 'avem.StreamDescriptor')
        file_contents = replace_variants(file_contents, 'StreamFormat', 'avem.StreamFormat')
        file_contents = replace_variants(file_contents, 'StreamIdentification', 'avem.StreamIdentification')
        file_contents = replace_variants(file_contents, 'StreamInfo', 'avem.StreamInfo')
        file_contents = replace_variants(file_contents, 'StreamInputCounterValidFlags', 'avem.StreamInputCounterValidFlags')
        file_contents = replace_variants(file_contents, 'StreamOutputCounterValidFlags', 'avem.StreamOutputCounterValidFlags')
        file_contents = replace_variants(file_contents, 'StreamPortDescriptor', 'avem.StreamPortDescriptor')
        file_contents = replace_variants(file_contents, 'StringsDescriptor', 'avem.StringsDescriptor')
        file_contents = replace_variants(file_contents, 'TimingDescriptor', 'avem.TimingDescriptor')
        file_contents = replace_variants(file_contents, 'UniqueIdentifier', 'avem.UniqueIdentifier')

        file_contents = file_contents.replace('avem.AudioClusterNodeDynamicModel', 'AudioClusterNodeDynamicModel')
        file_contents = file_contents.replace('avem.AudioClusterNodeModels', 'AudioClusterNodeModels')
        file_contents = file_contents.replace('avem.AudioClusterNodeStaticModel', 'AudioClusterNodeStaticModel')
        file_contents = file_contents.replace('avem.AudioMapNodeModels', 'AudioMapNodeModels')
        file_contents = file_contents.replace('avem.AudioMapNodeStaticModel', 'AudioMapNodeStaticModel')
        file_contents = file_contents.replace('avem.AudioUnitNodeDynamicModel', 'AudioUnitNodeDynamicModel')
        file_contents = file_contents.replace('avem.AudioUnitNodeStaticModel', 'AudioUnitNodeStaticModel')
        file_contents = file_contents.replace('avem.AvbInterfaceCounters', 'AvbInterfaceCounters')
        file_contents = file_contents.replace('avem.AvbInterfaceInfo', 'AvbInterfaceInfo')
        file_contents = file_contents.replace('avem.AvbInterfaceInfo', 'AvbInterfaceInfo')
        file_contents = file_contents.replace('avem.AvbInterfaceNodeDynamicModel', 'AvbInterfaceNodeDynamicModel')
        file_contents = file_contents.replace('avem.AvbInterfaceNodeStaticModel', 'AvbInterfaceNodeStaticModel')
        file_contents = file_contents.replace('avem.ClockDomainCounters', 'ClockDomainCounters')
        file_contents = file_contents.replace('avem.ClockDomainNodeDynamicModel', 'ClockDomainNodeDynamicModel')
        file_contents = file_contents.replace('avem.ClockDomainNodeStaticModel', 'ClockDomainNodeStaticModel')
        file_contents = file_contents.replace('avem.ClockSourceNodeDynamicModel', 'ClockSourceNodeDynamicModel')
        file_contents = file_contents.replace('avem.ClockSourceNodeStaticModel', 'ClockSourceNodeStaticModel')
        file_contents = file_contents.replace('avem.ControlNodeDynamicModel', 'ControlNodeDynamicModel')
        file_contents = file_contents.replace('avem.ControlNodeModels', 'ControlNodeModels')
        file_contents = file_contents.replace('avem.ControlNodeStaticModel', 'ControlNodeStaticModel')
        file_contents = file_contents.replace('avem.EntityCounters', 'EntityCounters')
        file_contents = file_contents.replace('avem.JackNodeDynamicModel', 'JackNodeDynamicModel')
        file_contents = file_contents.replace('avem.JackNodeStaticModel', 'JackNodeStaticModel')
        file_contents = file_contents.replace('avem.LocaleNodeStaticModel', 'LocaleNodeStaticModel')
        file_contents = file_contents.replace('avem.MemoryObjectNodeDynamicModel', 'MemoryObjectNodeDynamicModel')
        file_contents = file_contents.replace('avem.MemoryObjectNodeStaticModel', 'MemoryObjectNodeStaticModel')
        file_contents = file_contents.replace('avem.PtpInstanceNodeDynamicModel', 'PtpInstanceNodeDynamicModel')
        file_contents = file_contents.replace('avem.PtpInstanceNodeStaticModel', 'PtpInstanceNodeStaticModel')
        file_contents = file_contents.replace('avem.PtpPortNodeDynamicModel', 'PtpPortNodeDynamicModel')
        file_contents = file_contents.replace('avem.PtpPortNodeModels', 'PtpPortNodeModels')
        file_contents = file_contents.replace('avem.PtpPortNodeStaticModel', 'PtpPortNodeStaticModel')
        file_contents = file_contents.replace('avem.StreamConnections', 'StreamConnections')    # ??
        file_contents = file_contents.replace('avem.StreamDynamicInfo', 'StreamDynamicInfo')
        file_contents = file_contents.replace('avem.StreamInputConnectionInfo', 'StreamInputConnectionInfo')
        file_contents = file_contents.replace('avem.StreamInputCounters', 'StreamInputCounters')
        file_contents = file_contents.replace('avem.StreamInputNodeDynamicModel', 'StreamInputNodeDynamicModel')
        file_contents = file_contents.replace('avem.StreamNodeStaticModel', 'StreamNodeStaticModel')
        file_contents = file_contents.replace('avem.StreamNodeStaticModel', 'StreamNodeStaticModel')
        file_contents = file_contents.replace('avem.StreamOutputCounters', 'StreamOutputCounters')
        file_contents = file_contents.replace('avem.StreamOutputNodeDynamicModel', 'StreamOutputNodeDynamicModel')
        file_contents = file_contents.replace('avem.StreamPortNodeDynamicModel', 'StreamPortNodeDynamicModel')
        file_contents = file_contents.replace('avem.StreamPortNodeStaticModel', 'StreamPortNodeStaticModel')
        file_contents = file_contents.replace('avem.StringsNodeModels', 'StringsNodeModels')
        file_contents = file_contents.replace('avem.StringsNodeStaticModel', 'StringsNodeStaticModel')
        file_contents = file_contents.replace('avem.TimingNodeDynamicModel', 'TimingNodeDynamicModel')
        file_contents = file_contents.replace('avem.TimingNodeStaticModel', 'TimingNodeStaticModel')
        file_contents = file_contents.replace('avem.StreamInputNodeModels', 'StreamInputNodeModels')
        file_contents = file_contents.replace('avem.StreamOutputNodeModels', 'StreamOutputNodeModels')
        file_contents = file_contents.replace('avem.TimingNodeModels', 'TimingNodeModels')
        file_contents = file_contents.replace('avem.ConfigurationNodeStaticModel', 'ConfigurationNodeStaticModel')
        file_contents = file_contents.replace('avem.ConfigurationNodeDynamicModel', 'ConfigurationNodeDynamicModel')
        file_contents = file_contents.replace('avem.AvbInterfaceNodeModels', 'AvbInterfaceNodeModels')
        file_contents = file_contents.replace('avem.ClockSourceNodeModels', 'ClockSourceNodeModels')
        file_contents = file_contents.replace('avem.MemoryObjectNodeModels', 'MemoryObjectNodeModels')
        file_contents = file_contents.replace('avem.EntityNodeStaticModel', 'EntityNodeStaticModel')
        file_contents = file_contents.replace('avem.EntityNodeDynamicModel', 'EntityNodeDynamicModel')
        file_contents = file_contents.replace('avem.ClockDomainNodeModels', 'ClockDomainNodeModels')

        file_contents = file_contents.replace('avem.AudioMappings', 'avem.AudioMappingVector')
        file_contents = file_contents.replace('avem.MsrpMappings', 'avem.MsrpMappingVector')
        file_contents = file_contents.replace('avem.PathSequence', 'avem.UniqueIdentifierVector')

        file_contents = file_contents.replace('"enum avem.', '"')

        # process nih namespace
        file_contents = regex_variants(file_contents, r'la::networkInterface::([^\s]+)( const)?( &)?', r'nih.\g<1>')

        file_contents = replace_variants(file_contents, 'MacAddress', 'nih.MacAddress')
        return file_contents

modify("avdecc.py", AvdeccPatcher)