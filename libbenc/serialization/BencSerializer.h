#ifndef BENC_SERIALIZER_H
#define BENC_SERIALIZER_H

#include "libbenc/benc.h"

struct BencSerializer
{
    /**
     * Serialize a string and write to a writer.
     *
     * @param writer the Writer to write to.
     * @param string the string to write.
     * @return whatever the Writer returns when writing.
     */
    int32_t (* const serializeString)(const struct Writer* writer,
                                      const String* string);

    /**
     * Parse a string, reading in with the first callback and writing to the second.
     *
     * @param reader a Reader which will be asked for the data to parse. This implementation
     *               assumes the reader's pointer is alligned on the first digit of the length
     *               of the string and will leave the read pointer on the first character AFTER
     *               the end of the string.
     * @param writer a MemAllocator which will be used to store data.
     * @param stringPointer a pointer which will be set to the string.
     * @return 0 if everything goes well, -1 if NULL returned by the writer indicating an array
     *           overflow, -2 if -1 returned by the reader indicating an array underflow,
     *           -3 if content unparsable.
     */
    int32_t (* const parseString)(const struct Reader* reader,
                                  const struct MemAllocator* allocator,
                                  String** stringPointer);

    /**
     * Write an integer as decimal in bencoded format.
     * the integer 10 would be written as "i10e"
     *
     * @param writer the Writer to write to.
     * @param integer the number to write.
     * @return whatever the Writer returns when writing.
     */
    int32_t (* const serializeInteger)(const struct Writer* writer,
                                       Integer integer);

    /**
     * Parse an integer, read in with the reader and set the intPointer to the value of the int.
     *
     * @param reader a Reader which will be asked for the data to parse. This implementation
     *               assumes the reader's pointer is alligned on the 'i' which begins the integer
     *               and will leave the read pointer on the first character AFTER the 'e' which
     *               ends the integer.
     * @param output a pointer to a memory location which will be set to the value of the int.
     * @return 0 if everything goes well, -2 if -1 returned by the reader indicating an
     *           array underflow, -3 if content unparsable.
     */
    int32_t (* const parseInteger)(const struct Reader* reader,
                                   Integer* output);

    /**
     * Serialize a list.
     *
     * @param writer the Writer to write to.
     * @param List the list to serialize.
     * @return whatever the Writer returns when writing.
     */
    int32_t (* const serializeList)(const struct Writer* writer,
                                    const List* list);

    /**
     * Parse a list.
     *
     * @param reader a Reader which will be asked for the data to parse. This implementation
     *               assumes the reader's pointer is alligned on the 'l' which signifies the
     *               beginning of the list. This will leave the pointer on the first character
     *               AFTER the 'e' which signifies the end of the list.
     * @param allocator a MemAllocator which will be used to store data.
     * @param output a pointer which will be set to the location of the List.
     * @return 0 if everything goes well, -2 if -1 returned by the reader indicating an array
     *           underflow, -3 if content unparsable.
     */
    int32_t (* const parseList)(const struct Reader* reader,
                                const struct MemAllocator* allocator,
                                List* output);

    /**
     * Serialize a dictionary.
     *
     * @param writer the Writer to write to.
     * @param dictionary the dictionary to serialize.
     * @return whatever the Writer returns when writing.
     */
    int32_t (* const serializeDictionary)(const struct Writer* writer,
                                          const Dict* dictionary);

    /**
     * Parse a dictionary, reading in with the first callback and writing to the second.
     *
     * @param reader a Reader which will be asked for the data to parse. This implementation
     *               assumes the reader's pointer is alligned on the 'd' which indicates
     *               dictionary and will leave the read pointer on the first character AFTER
     *               the 'e' which ends the dictionary.
     * @param allocator a MemAllocator which will be used to store data.
     * @param output a dictionary pointer which will be set to the output. Dict* out = NULL; is enough.
     * @return 0 if everything goes well -2 if -1 returned by read indicating an array underflow,
     *           -3 if content unparsable.
     */
    int32_t (* const parseDictionary)(const struct Reader* reader,
                                      const struct MemAllocator* allocator,
                                      Dict* output);
};

#endif