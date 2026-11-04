import io.kaitai.struct.*;
import java.lang.reflect.*;
import java.nio.file.*;

// Usage: Dump <class> <bin> <out>: read, fetch instances, write into a same-size buffer.
public class Dump {
    public static void main(String[] a) throws Exception {
        for (int i = 0; i + 2 < a.length; i += 3) {
            try {
                Class<?> c = Class.forName("io.kaitai.struct.testwrite." + a[i]);
                KaitaiStream in = new ByteBufferKaitaiStream(a[i + 1]);
                KaitaiStruct.ReadWrite r = (KaitaiStruct.ReadWrite) c.getConstructor(KaitaiStream.class).newInstance(in);
                r._read();
                r._fetchInstances();
                byte[] out = new byte[(int) in.size()];
                ByteBufferKaitaiStream io = new ByteBufferKaitaiStream(out);
                r._write(io);
                Files.write(Paths.get(a[i + 2]), out);
            } catch (Throwable e) {
                Throwable t = e instanceof InvocationTargetException ? e.getCause() : e;
                Files.write(Paths.get(a[i + 2] + ".err"), (t.toString()).getBytes());
            }
        }
    }
}
