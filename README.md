# Concat_Tool

I made this tool to concatenate files which have been split. I downloaded a Udemy course and it was in parts so some videos had been split into 2 parts and the second part could not be played because it was missing the metadata.
Merging the files is quite easy in linux and other unix like systems. You just need to use the "cat" command and pipe it into the output file and do the same with the second one. But I'm on Windows and the Powershell and CMD are too slow for this.
So I wrote this tool in C to concatenate the binary data of 2 files.

###Usage: ./concat_tool INPUT_FILES... OUTPUT_FILE

Options:
-h, --help      Show this help message and exit.

###Arguments:
INPUT_FILES     List of input files to be concatenated in the specified order.
OUTPUT_FILE     Path to the output file where the concatenated content will be saved.

###Example:
./concat_tool file1.mp4 file2.mp4 file3.mp4 output.mp4
