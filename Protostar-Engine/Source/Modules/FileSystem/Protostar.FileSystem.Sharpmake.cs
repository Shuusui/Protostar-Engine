using System.IO;
using Sharpmake;

namespace Protostar
{
    [Generate]
    public class FileSystem : Module
    {
        public FileSystem()
        {
            SourceRootPath = Path.Combine("[project.SharpmakeCsPath]", "Source");
        }
    }
}