
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include"Դ.h"


//ExeFile->FileBuffer  ����ֵΪ���������ļ���С
//��ȡһ��exe�ļ���Ȼ�����ΪFileBuffer
DWORD ReadPEFile(IN const char* lpszFile, OUT LPVOID* pFileBuffer)
{
    //�����и�IN��OUT��������˼���ǲ��������ʹ������֮�󲻽��к���չ��
    //ɶҲ���ɣ���ʹ���ɸɣ�Ҳ����չ�ɿհף������C++�﷨������ģ�
    //LPSTR  ---->  typedef CHAR *LPSTR, *PSTR; ��˼����char* ָ�룻��WINNT.Hͷ�ļ�����
    FILE* pFile = NULL;
    //����һ��FILE�ṹ��ָ�룬�ڱ�׼��Stdio.h�ļ�ͷ����
    //�ɲο���https://blog.csdn.net/qq_15821725/article/details/78929344
    DWORD fileSize = 0;
    // typedef unsigned long       DWORD;  DWORD���޷���4���ֽڵ�����
    LPVOID pTempFileBuffer = NULL;
    //LPVOID ---->  typedef void far *LPVOID;��WINDEF.Hͷ�ļ����棻������voidָ������

    //���ļ�
    pFile = fopen(lpszFile, "rb"); //lpszFile�ǵ����������ݽ���
    if (!pFile)
    {
        printf("���ļ�ʧ��!\r\n");
        return 0;
    }
    /*
    ������ָ�������н����жϵĲ��������������ֵ�����ʹ�һ������������£�
    1.��Ϊָ���ж϶�Ҫ��NULL�Ƚϣ��൱��0����ֵ�����඼����ֵ
    2.if(!pFile)��if(pFile == NULL), ----> Ϊ�գ���ִ����䣻�������������ںŲ���һ�����ں�
    3.if(pFile)����if(pFile != NULL), ��Ϊ�գ���ִ����䣻
    */

    //��ȡ�ļ����ݺ󣬻�ȡ�ļ��Ĵ�С
    fseek(pFile, 0, SEEK_END);
    fileSize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    /*
    fseek ͨ��ʹ�ö����Ƶķ�ʽ���ļ����ƶ��ļ���дָ���λ��,��stdio.hͷ�ļ���

    int fseek(FILE * stream, long offset, int fromwhere);

    ������fseek�ĺ���ԭ��
    ��һ������stream Ϊ�ļ�ָ��
    �ڶ�������offset Ϊƫ������������ʾ����ƫ�ƣ�������ʾ����ƫ��
    ����������fromwhere Ϊָ�����ʼλ��,�趨���ļ������￪ʼƫ��,����ȡֵΪ��SEEK_CUR��SEEK_END��SEEK_SET
    SEEK_SET 0 �ļ���ͷ
    SEEK_CUR 1 ��ǰ��д��λ��
    SEEK_END 2 �ļ�β��

    ����������÷������ӣ�
����fseek(fp,100L,0);��fpָ���ƶ������ļ���ͷ100�ֽڴ���
����fseek(fp,100L,1);��fpָ���ƶ������ļ���ǰλ��100�ֽڴ���
    fseek(fp,100L,2);��fpָ���˻ص����ļ���β100�ֽڴ���
    fseek(fp,0,SEEK_SET);����дλ���ƶ����ļ���ͷ;
    fseek(fp,0,SEEK_END);����дλ���ƶ����ļ�βʱ;
    fseek(fp,100L,SEEK_SET);����дλ���ƶ������ļ���ͷ100�ֽڴ���
    fseek(fp,100L,SEEK_CUR);����дλ���ƶ������ļ���ǰλ��100�ֽڴ���
    fseek(fp,-100L,SEEK_END);����дָ���˻ص����ļ���β100�ֽڴ���
    fseek(fp,1234L,SEEK_CUR);�Ѷ�дλ�ôӵ�ǰλ������ƶ�1234�ֽ�;
    fseek(fp,0L,2);�Ѷ�дλ���ƶ����ļ�β;
    ���� --->  L��׺��ʾ������

    ftell()���ڷ����ļ���ǰָ��ָ���λ�ã���fseek��Ͽ�������ļ�Ԫ������������
    �ο���http://c.biancheng.net/cpp/html/2519.html

    ftell()����������ȡ�ļ���дָ��ĵ�ǰλ�ã���ԭ��Ϊ��long ftell(FILE * stream); ͬ����stdio.hͷ�ļ���
    ������stream Ϊ�Ѵ򿪵��ļ�ָ�롣
    */

    //��̬�����ڴ�ռ�
    pTempFileBuffer = malloc(fileSize);

    /*
    �ο���http://c.biancheng.net/cpp/html/137.html
    ԭ�ͣ�void* malloc (size_t size);
    size_t ---> typedef unsigned int size_t; �޷������ͱ�����size_t
    void*  ---> �����ķ���ֵ������ void* ��void������˵û�з���ֵ���߷��ؿ�ָ�룬���Ƿ��ص�ָ������δ֪;
    ������ʹ�� malloc() ʱͨ����Ҫ����ǿ������ת������ void ָ��ת��������ϣ��������;
    ���磺char *ptr = (char *)malloc(10);  //����10���ֽڵ��ڴ�ռ䣬��������ַ�
    ����˵�� ---> size Ϊ��Ҫ������ڴ�ռ�Ĵ�С�����ֽڣ�Byte���ơ�
    ����˵�� ---> malloc()�ڶ�������һ��ָ����С���ڴ�ռ䣬����������ݡ�����ڴ�ռ��ں���ִ����ɺ󲻻ᱻ��ʼ��;
    ���ǵ�ֵ��δ֪�ģ����Է�������ڴ�֮����Ҫ��ʼ����
    ����ֵ:����ɹ�����ָ����ڴ�ĵ�ַ��ʧ���򷵻� NULL��
    */

    if (!pTempFileBuffer)
    {
        printf("�ڴ����ʧ��!\r\n");
        fclose(pFile);
        return 0;
    }

    //�������뵽���ڴ�ռ䣬��ȡ����

    size_t n = fread(pTempFileBuffer, fileSize, 1, pFile);
    if (!n)
    {
        printf("��ȡ����ʧ��!\r\n");
        free(pTempFileBuffer);   // �ͷ��ڴ�ռ�
        fclose(pFile);           // �ر��ļ���
        return 0;
    }

    //���ݶ�ȡ�ɹ����ر��ļ�
    *pFileBuffer = pTempFileBuffer;  // ����ȡ�ɹ����������ڵ��ڴ�ռ���׵�ַ����ָ������pFileBuffer
    pTempFileBuffer = NULL;  // ��ʼ�������ʱ������ڴ�ռ�
    fclose(pFile);           // �ر��ļ�
    return fileSize;         // ���ػ�ȡ�ļ��Ĵ�С
}

//CopyFileBuffer --> ImageBuffer
//����ȡ��FileBuffer������ص�ImageBuffer������������֤�ļ����죻
DWORD CopyFileBufferToImageBuffer(IN LPVOID pFileBuffer, OUT LPVOID* pImageBuffer)
{
    //LPVOID ---->  typedef void far *LPVOID;��WINDEF.Hͷ�ļ����棻������voidָ������
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    LPVOID pTempImageBuffer = NULL;
    /*
    ���涼��PE�������ؽṹ�����ͣ�ʹ�������ͽ����Զ������������ʼ��ֵΪNULL
    PIMAGE_DOS_HEADER ---> ָ��ṹ�壬����Ϊ������ IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER
    PIMAGE_NT_HEADERS ---> ָ��ṹ�壬typedef PIMAGE_NT_HEADERS32    PIMAGE_NT_HEADERS;
    PIMAGE_FILE_HEADER ---> ָ��ṹ�壬����Ϊ������ IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;
    PIMAGE_OPTIONAL_HEADER32 ---> ָ��ṹ�壬����Ϊ������ IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;
    PIMAGE_SECTION_HEADER ---> ָ��ṹ�壬����Ϊ������ IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;
    */

    if (pFileBuffer == NULL)
    {
        printf("FileBuffer ��ȡʧ��!\r\n");
        return 0;
    }

    //�ж��Ƿ�����Ч��MZ��־
    if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
    {
        printf("��Ч��MZ��ʶ\r\n");
        return 0;
    }
    /*
    IMAGE_DOS_SIGNATURE �����ͷ�ļ�WINNT.H���棬��Ӧ�Ǹ��޲����ꣻ
    #define IMAGE_DOS_SIGNATURE                 0x5A4D      // MZ
    �ں���չ��ʱ��ͻ��滻Ϊ0x5A4D ��Ȼ����ݼܹ��Ĳ�ͬ��������洢���ִ�˺�С��ģʽ��
    ʹ�����淽ʽ���бȶ��Ƿ�����Ч��MZͷ�Ƿǳ���Ч��
    ����IMAGE_DOS_SIGNATURE�洢��ֵ�������ֽڣ��պþ���PWORD ---> typedef WORD near *PWORD;
    �����ڽ��бȽϵ�ʱ����Ҫǿ������ת��Ϊ��ͬ�����ͽ��бȽ�
    */

    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    //����Ķ��壬���൱���Ѿ�ȷ���ˣ���ͷ�϶���MZ�ˣ�Ȼ��ǿ��ת������ΪPIMAGE_DOS_HEADER������Dosͷ

    //�ж��Ƿ�����Ч��PE��־
    if (*((PDWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("��Ч��PE���\r\n");
        return 0;
    }
    /*
    IMAGE_NT_SIGNATURE  ---> #define IMAGE_NT_SIGNATURE   0x00004550  // PE00
    ����ͬ���Ǹ�����չ����ͷ�ļ�WINNT.H���棻
    �ڽ��бȶԵ�ʱ����Ϊ��Dosͷ�����и�ֵ�� e_lfanew ��Ӧ��ʱ��DWORD���ͣ������ڽ���ָ����ӵ�ʱ��
    ��Ҫ�Ƚ���ǿ������ת����Ȼ����ӣ����ƶ�ָ��λ�ã�Ȼ��������Ҫ�ȶԵĽ����0x4550վ�����ֽ�
    ������Ҫǿ��ת������ΪPWORD��
    */
    //��λNTͷ
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
    //����ƫ�����֮��pFileBuffer��ָ��ƫ�Ƶ���NTͷ---> pNTHeader
    //****************************************************************************************
    //��λPE�ļ�ͷ
    pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);
    //����PEͷ�Ľṹ�����ݣ�PE�ļ�ͷλ����NTͷ�׵�ַƫ��4���ֽڼ��ɵõ�pPEHeader
    //****************************************************************************************
    //��λ��ѡPEͷ
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
    /*
    Ҫ�õ���ѡPE���׵�ַλ�ã��͸�������õ���PE�ļ�ͷλ�������IMAGE_SIZEOF_FILE_HEADER����λ��
    IMAGE_SIZEOF_FILE_HEADERҲ�Ǹ�����չ�������ֽ�������PE�ļ�ͷ�Ĵ�С��20���ֽڣ�
    #define IMAGE_SIZEOF_FILE_HEADER  20������ֻҪ��PE�ļ�ͷ���׵�ַƫ��20���ֽڼ����ƶ�����ѡPEͷ��
    ָ����ӵ�ʱ�򣬴˴���������Ȼ��DWORD
    */
    //****************************************************************************************
    //��һ���ڱ�ָ��
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);
    /*
    ����Ҫ�ƶ�����һ���ڱ�ָ����׵�ַ������Ҫ���������׼PE�ļ�ͷ�е�SizeOfOptionalHeader��ȡ�����ѡPE
    ͷ�Ĵ�С��Ȼ����������С����ƫ�Ƽ��ɣ�
    */
    //****************************************************************************************

    /*
    ���˽ڱ���׵�ַλ��֮����Ϊ��Ҫ��FileBuffer���Ƶ�ImageBuffer����������У��ڱ�֮ǰ��Dosͷ��NTͷ
    PE�ļ�ͷ����ѡPEͷ�����ǵĴ�С���ǲ���ģ����Զ�λ����֮�󣬵�����Ĳ�����ֱ�Ӹ��Ƽ��ɣ����ڱ�һ��
    ����FileBuffer״̬��ImageBuffer״̬�ǲ���ͬ�ģ����ǽڱ�֮�临��ת����ImageBuffer����Ҫ�����ڱ�����
    �ڲ�����ʱ������Ҫȷ��FileBuffer��ImageBuffer֮��ImageBuffer�Ĵ�С�Ƕ��٣��������С���Ѿ��ڿ�ѡPEͷ
    �����ĳһ��ֵ���Ѿ��������� ---> SizeOfImage ;
    ע�⣺FileBuffer��ImageBuffer�������ڴ��е�չʾ��ֻ����FileBuffer��ʹ��winhex�����Ƶ���ʽ�򿪲鿴��
    �����Ƶ���ʽ����ImageBuffer����˫����Ӧ�ó��򣬽���������ڴ�����ʾ�Ķ����Ƶ���ʽ��
    */
    //****************************************************************************************

    //����SizeOfImage�����µ��ڴ�ռ�
    pTempImageBuffer = malloc(pOptionHeader->SizeOfImage);

    if (!pTempImageBuffer)
    {
        printf("�ٴ��ڶ�������һ���ڴ�ռ�ʧ��\r\n");
        return 0;
    }

    //��Ϊ����Ҫ��ʼ���ڴ�ռ���и��Ʋ�����������Ҫ��ʼ��������������Ϊ0�������������ݣ����������쳣
    //��ʼ���µĻ�����
    memset(pTempImageBuffer, 0, pOptionHeader->SizeOfImage);
    /*
    �ο���http://c.biancheng.net/cpp/html/157.html

    ��ͷ�ļ�string.h����

    void* memset( void* ptr,int value,size_t num );
    memset()����������ָ���ڴ��ǰn���ֽ�����Ϊ�ض���ֵ;

    ����˵����
    ptr     ΪҪ�������ڴ��ָ��;
    value   ΪҪ���õ�ֵ;�ȿ�����value����int���͵�ֵ,Ҳ���Դ���char���͵�ֵ,int��char���Ը���ASCII���໥ת��;
    num     Ϊptr��ǰnum���ֽ�,size_t����unsigned int��
    ����˵����memset()�Ὣptr��ָ���ڴ������ǰnum���ֽڵ�ֵ������Ϊvalue,Ȼ�󷵻�ָ��ptr��ָ��;
    */
    //****************************************************************************************

    //����SizeOfHeaders��С��ȷ�����ȸ���Dosͷ
    memcpy(pTempImageBuffer, pDosHeader, pOptionHeader->SizeOfHeaders);
    /*
    �ο���http://c.biancheng.net/cpp/html/155.html

    ��ͷ�ļ�string.h����

    void* memcpy (void* dest,const void* src,size_t num);
    memcpy()�����������������ڴ�ģ����Ḵ��src��ָ�����ݵ��׵�ַ����Ϊ��ʼλ�ã�Ȼ��ƫ��num���ֽڵ�dest��ָ���ڴ��ַ
    ��λ�ã��˺����и��������ǣ����������ı����Ƶ��������ͣ�ֻ�����ֽڵؽ��и��ƣ����������ʹ�ô����˺ܴ������ԣ�
    ���������κ��������ͽ��и��ƣ�

    ��Ҫע����ǣ�
    dest ָ��Ҫ�����㹻�Ŀռ䣬Ҳ����Ҫ���ڵ���num�ֽڵĿռ䣬���û�з����㹻�Ŀռ����ִ���
    dest��src��ָ���ڴ�ռ䲻���ص�������������ص���ʹ�� memmove() ����Ӱ�ȫ����

    ��������Ĵ���ĺ������£�
    (1)pDosHeader ---> ��ָ��pFileBuffer���׵�ַ��Ҳ�����ڴ渴�Ƶ�ʱ������￪ʼ��
    (2)pTempImageBuffer  ---> �����Ǳ�ʾ����Ҫ���Ƶ�Ŀ�ģ�Ҫ�����ݸ��Ƶ�����ڴ�����
    (3)pOptionHeader->SizeOfHeaders  ---> �����ʾ���ƶ������ݵ�pTempImageBuffer����ȥ��
    (4)�����濴�����Ǿ�֪�����Ƶ�Ŀ��pOptionHeader->SizeOfHeaders���ڵ��ڴ�ռ�һ��Ҫ��pTempImageBuffer��
    */
    //****************************************************************************************

    //������Ѿ�ȷ����ͷ�����ƺ��ˣ���ô����Ϳ��Կ�ʼ���ƽڵ���������ݣ���Ϊ�ڲ�������һ����������Ҫ�õ�forѭ�����в���
    //���ݽڱ�ѭ��copy�ڵ�����
    PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;
    //����һ����ʱ�ڱ��ָ��
    for (int i = 0; i < pPEHeader->NumberOfSections; i++, pTempSectionHeader++)
    {
        memcpy((void*)((DWORD)pTempImageBuffer + pTempSectionHeader->VirtualAddress),
            (void*)((DWORD)pFileBuffer + pTempSectionHeader->PointerToRawData), pTempSectionHeader->SizeOfRawData);
    }
    /*
    ����Ĵ�Ų������Ǹ��ݱ�׼PE�ļ�ͷ�����ֵ NumberOfSectionsȷ���м����ڣ�Ȼ�󲻶ϵļ��㲢����ָ��ƫ��λ�ã���ͣ�ĸ���

    PointerToRawData   ---> �����ļ��е�ƫ�Ƶ�ַ��
    VirtualAddress     ---> �����ڴ��е�ƫ�Ƶ�ַ;
    SizeOfRawData      ---> �����ļ��ж����ĳߴ�;

    (void*)((DWORD)pTempImageBuffer + pTempSectionHeader->VirtualAddress)   ---> Dest��Ŀ�ĵأ�
    ���������Ѿ�֪���˺���memcpy����ô���Ʋ����ģ����������������������£�
    ��������֪��������չʾ����Ŀ�ĵأ��������ǵ�Ŀ����Ҫ��FileBuffer�����ݸ��Ƶ�ImageBuffer�ڵ����ݣ�
    ��ôҪʹ�õ������ļ���˫����֮�����ڴ��е�ƫ�Ƶ�ַ�������ַ����VirtualAddress������ٸ�����:
    ������notepad.exe,Ȼ��ʹ��winhex�������notepad.exe���ڴ����ݣ�ͬʱʹ��PE�������ߵõ�����ֵ����Ϣ���£�
    ��ѡPEͷ ---> ImageBase   ---> 0x01000000
    ��һ���ڱ���ʾ��VirtualAddress  ---> 00001000
    ��������ֵ��Ӿ͵õ����ļ��������ڴ��е�һ���ڵ���ʵ���ݵ���ʼλ�� ---> 0x01001000
    �鿴winhex��Ӧ�ĵ�ַ��ȷ���ǶԵģ�

    (void*)((DWORD)pFileBuffer + pTempSectionHeader->PointerToRawData)      ---> Src��Դ���Ƶ���ʼ�ڴ��ַ��
    ͬ������������ӣ�
    PointerToRawData�ǽ����ļ��е�ƫ�Ƶ�ַ��������֪�������ļ��к����ڴ����ǲ�һ���ģ���Ϊ���ڴ�����ImageBase��˵����
    �����ļ���û�У�����������ʼλ�þ����ļ��洢��Ӳ�̵�ʱ��ʹ��winhex�򿪵Ŀ�ͷλ�ã�Ϊ����ͬ��ʹ��winhex�Զ����Ƶ���ʽ
    ��notepad.exe����˫���򿪣��������ļ�����ʼλ����0x00000000��ͬʱʹ��PE��������ȷ�ϳ���PointerToRawData��ֵ
    PointerToRawData  ---> 0x00000400 ; ��ʼλ��Ϊ0x00000000 ,������Ӿ͵õ���һ���ڱ����ʼλ��Ϊ0x00000400
    �鿴winhex��Ӧ�ĵ�ַ��ȷ���ǶԵģ�
    ���������ܽ�������Src�������ڴ渴�Ƶ�ʱ�򣬴����ƫ�Ƶ�ַ��ʼ�����ݿ�ʼ���ƣ�

    pTempSectionHeader->SizeOfRawData
    ������Ǹ����������渴��Ҫ���ƶ������ݵ� (void*)((DWORD)pTempImageBuffer + pTempSectionHeader->VirtualAddress)
    SizeOfRawData ---> �����ļ��ж����ĳߴ�;
    ���ӻ����������Ϊ����
    ͨ��PE��������ȷ��SizeOfRawData�Ĵ�СΪ��0x00007800

    �ܽ᣺
    memcpy((void*)((DWORD)pTempImageBuffer + pTempSectionHeader->VirtualAddress),
    (void*)((DWORD)pFileBuffer + pTempSectionHeader->PointerToRawData),
    pTempSectionHeader->SizeOfRawData);

    �������������ļ��е���ʽ�ҵ�Ҫ���Ƶ�λ��0x00000400����ʼλ�ÿ�ʼ���ƣ�Ҫ����0x00007800���ֽڴ�С��Ҳ���Ǵ�
    0x00000400�����ַ��ʼ���ƫ��7800���ֽڣ�����Щ���ݸ��Ƶ��ļ�˫������ʱ����ڴ��ַ0x01001000Ϊ�����󸲸Ǹ���
    ��ɼ��ɣ�Ϊ������������£�0x00000400+0x00007800=0x00007C00 ; 0x00007C00�����ַ�պ��ǵڶ����ڵ�PointerToRawData
    �����Ϳ��Ժܺõ����forѭ���Եڶ����ڵĸ��ƣ�
    */

    //****************************************************************************************
    //��������
    * pImageBuffer = pTempImageBuffer;
    //�����ƺú�ڵ��׵�ַ���浽ָ��pImageBuffer��
    pTempImageBuffer = NULL;
    //��ʼ�������ʱʹ�õ�pTempImageBuffer

    return pOptionHeader->SizeOfImage;
}

//FileBuffer ---> NewImageBuffer�������ڲ�����?
//ͨ������FileBuffer������1000H���µ�NewImageBuffer,���������ڣ�
DWORD CopyFileBufferToNewImageBuffer(IN LPVOID pFileBuffer, IN size_t fileSize, OUT LPVOID* pNewImageBuffer)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeder = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    PIMAGE_SECTION_HEADER pLastSectionHeader = NULL;
    LPVOID pTempNewImageBuffer = 0;
    DWORD sizeOfFile = 0;
    DWORD numberOfSection = 0;
    DWORD okAddSections = 0;


    //�ж϶�ȡpFileBuffer��ȡ�Ƿ�ɹ�
    if (!pFileBuffer)
    {
        printf("������ָ����Ч\r\n");
        return 0;
    }

    //�ж��Ƿ�ΪMZ��־

    if ((*(PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)// IMAGE_DOS_SIGNATURE --> MZ
    {
        printf("����һ����Ч��MZ��־\r\n");
        return 0;
    }

    //�ж��Ƿ�ΪPE��־
    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    if (*((PWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE) // IMAGE_NT_SIGNATURE --> PE
    {
        printf("������Ч��PE��־\r\n");
        return 0;
    }

    //*********************���뿪���ڴ�ռ�*****************************************************************

    sizeOfFile = fileSize + 0x1000;
    pTempNewImageBuffer = malloc(sizeOfFile);

    //�ж��ڴ�ռ俪���Ƿ�ɹ�
    if (!pTempNewImageBuffer)
    {
        printf("pTempNewImageBuffer�����ڴ�ռ�ʧ��\r\n");
        return 0;
    }

    //��ʼ���ڴ�����
    memset(pTempNewImageBuffer, 0, sizeOfFile);

    //��ʼ�����֮���Ȱ�Ϊ�޸ĵ��ڴ�ռ�ȫ���������µ��ڴ�ռ�
    memcpy(pTempNewImageBuffer, pFileBuffer, fileSize);

    //��λDosͷ��ַ
    pDosHeader = (PIMAGE_DOS_HEADER)(pTempNewImageBuffer);

    //��λNTͷ�ĵ�ַ
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pTempNewImageBuffer + pDosHeader->e_lfanew);

    //��λ��־PEͷ��ַ
    pPEHeder = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 0x04);//PE SIGNATURE վ4���ֽ�

    //��λ��ѡPEͷ��ַ
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)(((DWORD)pPEHeder) + IMAGE_SIZEOF_FILE_HEADER);//IMAGE_SIZEOF_FILE_HEADER -> 20���ֽ�

    //��λ��һ���ڱ��ַ
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeder->SizeOfOptionalHeader);

    //��λ���һ���ڱ�ĵ�ַ
    pLastSectionHeader = &pSectionHeader[pPEHeder->NumberOfSections - 1];

    //�ж��Ƿ����㹻�Ŀռ����һ���ڱ�
    //�ж�������
    /*
        SizeOfHeader - (DOS + �������� + PE��� + ��׼PEͷ + ��ѡPEͷ + �Ѵ��ڽڱ�) >= 2���ڱ�Ĵ�С
        SizeOfHeader�ڿ�ѡPEͷ����
    */

    okAddSections = (DWORD)(pOptionHeader->SizeOfHeaders - (pDosHeader->e_lfanew + 0x04 + \
        sizeof(PIMAGE_FILE_HEADER) + pPEHeder->SizeOfOptionalHeader + sizeof(PIMAGE_SECTION_HEADER) \
        * pPEHeder->NumberOfSections));

    if (okAddSections < 2 * sizeof(PIMAGE_SECTION_HEADER))
    {
        printf("���exe�ļ�ͷ��ʣ��ռ䲻��\r\n");
        free(pTempNewImageBuffer);
        return 0;
    }

    //����û���⣬�Ϳ�ʼ�޸�������
//*************************�޸�����*******************************************************************

    //��ʼ���½ڱ���Ϣ
    PWORD pNumberOfSection = &pPEHeder->NumberOfSections;
    PDWORD pSizeOfImage = &pOptionHeader->SizeOfImage;

    numberOfSection = pPEHeder->NumberOfSections;
    PVOID pSecName = &pSectionHeader[numberOfSection].Name;
    PDWORD pSecMisc = &pSectionHeader[numberOfSection].Misc.VirtualSize;
    PDWORD pSecVirtualAddress = &pSectionHeader[numberOfSection].VirtualAddress;
    PDWORD pSecSizeOfRawData = &pSectionHeader[numberOfSection].SizeOfRawData;
    PDWORD pSecPointToRawData = &pSectionHeader[numberOfSection].PointerToRawData;
    PDWORD pSecCharacteristics = &pSectionHeader[numberOfSection].Characteristics;

    //�޸�PE�ļ�ͷ����Ľ�������Ϣ

    printf("*pNumberOfSection:%#X \r\n", pPEHeder->NumberOfSections);
    *pNumberOfSection = pPEHeder->NumberOfSections + 1;
    printf("*pNumberOfSection:%#X \r\n", pPEHeder->NumberOfSections);

    //�޸�PE��ѡͷ����SizeOfImage��Ϣ
    printf("*pSizeOfImage:%#X \r\n", pOptionHeader->SizeOfImage);
    *pSizeOfImage = pOptionHeader->SizeOfImage + 0x1000;
    printf("*pSizeOfImage:%#X \r\n", pOptionHeader->SizeOfImage);

    //��ڱ����������

    memcpy(pSecName, ".newSec", 8);
    *pSecMisc = 0x1000;
    //����VirtualAddress�ĵ�ַ��Ҫ�������һ���ڱ��ж���ǰ�ڴ��е�ʵ�ʴ�С?
    //���ļ��ж����Ĵ�С���ֱ�ʹ��VirtualAddress�������ǵ�ֵ���ĸ��󣬾���
    //�ĸ���
    //VirtualAddress+max(VirtualSize,SizeOfRawData)
    //��������Ĺ�ʽ

    //�жϳ�Ҫ��ӵ�ֵ
    DWORD add_size = pLastSectionHeader->Misc.VirtualSize > pLastSectionHeader->SizeOfRawData ? \
        pLastSectionHeader->Misc.VirtualSize:pLastSectionHeader->SizeOfRawData;
    //�����Ǹ���Ŀ�����

    printf("pLastSectionHeader: %#X \r\n", pLastSectionHeader);
    printf("add_size: %#X \r\n", add_size);
    printf("numberOfSection: %#X \r\n", pPEHeder->NumberOfSections);
    printf("pLastSectionHeader->Misc.VirtualSize: %#X \r\n", pLastSectionHeader->Misc.VirtualSize);
    printf("pLastSectionHeader->SizeOfRawData: %#X \r\n", pLastSectionHeader->SizeOfRawData);
    printf("add_size: %#X \r\n", add_size);

    *pSecVirtualAddress = pLastSectionHeader->VirtualAddress + add_size;

    //SectionAlignment����

    if (*pSecVirtualAddress % pOptionHeader->SectionAlignment)
    {
        *pSecVirtualAddress = *pSecVirtualAddress / pOptionHeader->SectionAlignment * \
            pOptionHeader->SectionAlignment + pOptionHeader->SectionAlignment;
    }

    *pSecSizeOfRawData = 0x1000;
    *pSecPointToRawData = pLastSectionHeader->PointerToRawData + pLastSectionHeader->SizeOfRawData;

    //FileAlignment����

    if (*pSecPointToRawData % pOptionHeader->FileAlignment)
    {
        *pSecPointToRawData = *pSecPointToRawData / pOptionHeader->FileAlignment * \
            pOptionHeader->FileAlignment + pOptionHeader->FileAlignment;
    }

    *pSecCharacteristics = 0xFFFFFFFF;

    *pNewImageBuffer = pTempNewImageBuffer;
    pTempNewImageBuffer = NULL;

    return sizeOfFile;
}

//������Ĵ�С
//Actuall_size  ---> �ڴ��ж���ǰʵ�ʵĴ�С ---> VirtualSize
//Align_size  ---> �ļ��ж����Ĵ�С ---> SizeOfRawData
DWORD AlignLength(DWORD Actuall_size, DWORD Align_size)
{
    if (Actuall_size % Align_size == 0)
    {
        return Actuall_size;
    }
    else
    {
        DWORD n = Actuall_size / Align_size;
        return Align_size * (n + 1);
    }
}

//��һ�ֶ�����㷽ʽ
DWORD Alignment(DWORD alignment_value, DWORD addend, DWORD address)
{
    int n = 0;
    if (addend / alignment_value)
    {
        if (addend % alignment_value)
        {
            n = addend / alignment_value + 1;
        }
        else
        {
            n = addend / alignment_value;
        }
    }
    else
    {
        if (addend)
        {
            n = 1;
        }
        else
        {
            n = 0;
        }
    }
    address += n * alignment_value;
    return address;
}

//ImageBuffer ---> NewImageBuffer
//���������ص��ڴ��ImageBuffer���뵽NewImageBuffer���޸��������֮��׼�����̲���
DWORD FileBufferToModifyImageBuffer(IN LPVOID pFileBuffer, OUT LPVOID* pNewImageBuffer)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    PIMAGE_SECTION_HEADER pLastSectionHeader = NULL;
    LPVOID pTempNewImageBuffer = NULL;
    DWORD ImageBuffer_Size = 0;
    DWORD numberOfSection = 0;

    //�ж϶�ȡpImageBuffer�Ƿ�ɹ�
    if (!pFileBuffer)
    {
        printf("������ָ����Ч\r\n");
    }

    //�ж��Ƿ�����Ч��MZͷ
    if ((*(PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
    {
        printf("������Ч��MZͷ\r\n");
        return 0;
    }

    //�ж��Ƿ�����Ч��PEͷ
    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    if (*((PWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("������Ч��PEͷ\r\n");
        return 0;
    }

    //��λNTͷ
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);

    //��λ��׼��PE�ļ�ͷ
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x04);

    //��λ��ѡPEͷ
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);

    //��λ��һ���ڱ��ַ
    numberOfSection = pPEHeader->NumberOfSections;
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //��λ���һ���ڱ��ַ
    pLastSectionHeader = &pSectionHeader[numberOfSection - 1];
    //    printf("numberOfSection --> %#X \r\n",numberOfSection);
    //    printf("*pSectionHeader --> %#X \r\n",pSectionHeader->Misc.VirtualSize);
    //    printf("*pLastSectionHeader --> %#X \r\n",&pLastSectionHeader);

        //��ʼ������Ҫ�޸ĵĲ���

        //���һ�������ڴ��ж���ǰ�Ĵ�С��
    PDWORD pVirtualSize = &pLastSectionHeader->Misc.VirtualSize;
    //���һ�������ļ��ж����Ĵ�С��
    PDWORD pSizeOfRawData = &pLastSectionHeader->SizeOfRawData;
    //�ļ���SizeOfImage�Ĵ�С��
    PDWORD pSizeOfImage = &pOptionHeader->SizeOfImage;

    //��չ�޸�֮ǰ������
//    printf("&pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",pVirtualSize);
//    printf("*pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",*pVirtualSize);
//
//    printf("&pLastSectionHeader->SizeOfRawData --> %#X \r\n",pSizeOfRawData);
//    printf("*pLastSectionHeader->SizeOfRawData --> %#X \r\n",*pSizeOfRawData);
//
//    printf("&pOptionHeader->SizeOfImage --> %#X \r\n",pSizeOfImage);
//    printf("*pOptionHeader->SizeOfImage --> %#X \r\n",*pSizeOfImage);

    //��չ�޸�pVirtualSize
    * pVirtualSize = AlignLength(*pVirtualSize, pOptionHeader->SectionAlignment) + 0x1000;
    //    printf("&pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",pVirtualSize);
    //    printf("*pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",*pVirtualSize);
    //    printf("&pLastSectionHeader->SizeOfRawData --> %#X \r\n",pSizeOfRawData);
    //    printf("*pLastSectionHeader->SizeOfRawData --> %#X \r\n",*pSizeOfRawData);
    //
        //��չ�޸�pSizeOfRawData
    *pSizeOfRawData = AlignLength(*pSizeOfRawData, pOptionHeader->SectionAlignment) + 0x1000;
    //    printf("&pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",pVirtualSize);
    //    printf("*pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",*pVirtualSize);
    //    printf("&pLastSectionHeader->SizeOfRawData --> %#X \r\n",pSizeOfRawData);
    //    printf("*pLastSectionHeader->SizeOfRawData --> %#X \r\n",*pSizeOfRawData);
    //    printf("&pOptionHeader->SizeOfImage --> %#X \r\n",pSizeOfImage);
    //    printf("*pOptionHeader->SizeOfImage --> %#X \r\n",*pSizeOfImage);

        //�޸�SizeOfImage
    *pSizeOfImage += 0x1000;
    //    printf("&pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",pVirtualSize);
    //    printf("*pLastSectionHeader->Misc.VirtualSize --> %#X \r\n",*pVirtualSize);
    //    printf("&pLastSectionHeader->SizeOfRawData --> %#X \r\n",pSizeOfRawData);
    //    printf("*pLastSectionHeader->SizeOfRawData --> %#X \r\n",*pSizeOfRawData);
    //    printf("&pOptionHeader->SizeOfImage --> %#X \r\n",pSizeOfImage);
    //    printf("*pOptionHeader->SizeOfImage --> %#X \r\n",*pSizeOfImage);

        //�õ��޸�֮��Ĵ�С׼�������ڴ�ռ�

    ImageBuffer_Size = pOptionHeader->SizeOfImage;
    pTempNewImageBuffer = malloc(ImageBuffer_Size);

    if (!pTempNewImageBuffer)
    {
        printf("�����ڴ�ռ�ʧ��\r\n");
        return 0;
    }

    //��ʼ���ڴ�ռ�
    memset(pTempNewImageBuffer, 0, ImageBuffer_Size);

    //����SizeOfHeaders
    memcpy(pTempNewImageBuffer, pDosHeader, pOptionHeader->SizeOfHeaders);

    //������ʱ�ڵĽṹ��ָ�룬��������
    PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;

    for (DWORD i = 0; i < pPEHeader->NumberOfSections; i++, pTempSectionHeader++)
    {
        memcpy((PVOID)((DWORD)pTempNewImageBuffer + pTempSectionHeader->VirtualAddress), \
            (void*)((DWORD)pFileBuffer + pTempSectionHeader->PointerToRawData), pTempSectionHeader->SizeOfRawData);
    }

    *pNewImageBuffer = pTempNewImageBuffer;
    pTempNewImageBuffer = NULL;
    return *pSizeOfImage;
}

//��ImageBuffer����Ϊһ���ڱ�ͽ�Ȼ��ѹ��ΪNewBuffer��������׼��
DWORD ImageBufferMergeSections(IN LPVOID pImageBuffer, OUT LPVOID* pNewBuffer)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    PIMAGE_SECTION_HEADER pLastSectionHeader = NULL;
    LPVOID pTempMergeSection = NULL;
    DWORD finalSections_Size = 0;
    DWORD numberOfSection = 0;
    DWORD lastSectionsMax_Size = 0;
    DWORD sizeOfFile = 0;
    DWORD NewSecCharacteristics = 0;
    DWORD NewSectionsBuffer = 0;

    //�ж϶�ȡpImageBuffer�Ƿ�ɹ�
    if (pImageBuffer == NULL)
    {
        printf("������ָ����Ч\r\n");
    }
    //�ж��Ƿ�����Ч��MZ��־
    if (*((PWORD)pImageBuffer) != IMAGE_DOS_SIGNATURE)
    {
        printf("������Ч��MZͷ\r\n");
        free(pImageBuffer);
        return 0;
    }
    //�ж��Ƿ�����Ч��PE��־

    pDosHeader = (PIMAGE_DOS_HEADER)pImageBuffer;
    if (*((PDWORD)((DWORD)pImageBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("������Ч��PE��־\r\n");
        free(pImageBuffer);
        return 0;
    }


    //��λNTͷ
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pImageBuffer + pDosHeader->e_lfanew);

    //��λ��׼��PE�ļ�ͷ
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x04);

    //��λ��ѡPEͷ
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);

    //��λ��һ���ڱ��ַ
    numberOfSection = pPEHeader->NumberOfSections;
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //��λ���һ���ڱ��ַ
    pLastSectionHeader = &pSectionHeader[numberOfSection - 1];

    //����һ����ʱ�ڱ�ָ��
    PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;

    //�ȼ����SizeOfHeaders
    pOptionHeader->SizeOfHeaders = Alignment(pOptionHeader->SectionAlignment, pOptionHeader->SizeOfHeaders, 0);


    //���һ�������ڴ����ǰ�Ĵ�С��
    DWORD pVirtualSize = pLastSectionHeader->Misc.VirtualSize;
    //���һ�������ļ��ж����Ĵ�С��
    DWORD pSizeOfRawData = pLastSectionHeader->SizeOfRawData;

    //�������һ���������ֵ��SizeOfRawData����VirtualSize
    lastSectionsMax_Size = (pSizeOfRawData > pVirtualSize ? pSizeOfRawData : pVirtualSize);

    //����һ��
    if (!debug)
    {
        printf("pLastSectionHeader->SizeOfRawData: %#X \r\n", pSizeOfRawData);
        printf("pLastSectionHeader->Misc.VirtualSize: %#X \r\n", pVirtualSize);
        printf("lastSectionsMax_Size: %#X \r\n", lastSectionsMax_Size);
    }

    //�������պϲ���ڶ�ӦSizeOfRawData��VirtualSize�Ĵ�С
    finalSections_Size = (pLastSectionHeader->VirtualAddress + lastSectionsMax_Size - pOptionHeader->SizeOfHeaders);

    //���������һ���ڱ�,����������ǽ�ÿ���ڶ���Ϊ0
    for (DWORD i = 0; i < numberOfSection; i++, pTempSectionHeader++)
    {
        NewSecCharacteristics |= pTempSectionHeader->Characteristics;
        //���� |= ��λ��Ȼ��ֵ����ΪNewSecCharacteristicsΪ0�������µĽڶ�Ӧ��ֵҲ����Ϊ0��
        if (i > 0)
        {
            memset(&pSectionHeader[i], 0, IMAGE_SIZEOF_SECTION_HEADER);//��ÿ���ڶ���Ϊ0
        }
    }

    //IMAGE_SIZEOF_SECTION_HEADER --> 40

    //�޸ĵ�һ���ڵ�SizeOfRawData��VirtualSize��ֵ���������Ϊ����������������ֵ
    pSectionHeader->Misc.VirtualSize = finalSections_Size;
    pSectionHeader->SizeOfRawData = finalSections_Size;

    //�޸��½ڵ�Characteristics��ֵ
    pSectionHeader->Characteristics = NewSecCharacteristics;

    //�޸�pPEHeader->NumberOfSections������Ϊ0x01
    pPEHeader->NumberOfSections = 0x01;

    //��������һ��
    if (!debug)
    {
        printf("pSectionHeader->Characteristics: %#X \r\n", pSectionHeader->Characteristics);
        printf("pSectionHeader->SizeOfRawData: %#X \r\n", pSectionHeader->SizeOfRawData);
        printf("pSectionHeader->Misc.VirtualSize: %#X \r\n", pSectionHeader->Misc.VirtualSize);
    }

    //����SizeOfImage�����µĿռ�,���˴�˵�������Ѿ���������˸�����ص�����ֵ�����������ڴ�ռ�Ϊ������׼���ˣ�
    pTempMergeSection = malloc(pOptionHeader->SizeOfImage);

    //sizeOfFile = pOptionHeader->SizeOfHeaders + finalSections_Size;
    //ʹ��winhex��notepad.exe ��0x00000400�����ǵ�һ����֮ǰ�����д�С
    // for(DWORD i = 0;i<numberOfSection;i++)
    // {
    //     sizeOfFile += pSectionHeader[i].SizeOfRawData;  // pSectionHeader[i]��һ�ּӷ�
    // }

    //pTempNewBuffer = malloc(sizeOfFile);

    if (!pTempMergeSection)
    {
        printf("�����ڴ�ռ�ʧ��\r\n");
        return 0;
    }

    //��ʼ���µĻ�����
    memset(pTempMergeSection, 0, pOptionHeader->SizeOfImage);
    //����SizeOfHeaders ��copyͷ
    memcpy(pTempMergeSection, pDosHeader, pOptionHeader->SizeOfHeaders);
    //��ʼ���ƽڵ���Ϣ����Ϊ�����Ǻϲ��ڣ�ֻ��һ���ڣ����Բ���Ҫʹ��forѭ�����б������ƣ�ֱ�Ӹ��Ƽ��ɣ�
    memcpy((PDWORD)((DWORD)pTempMergeSection + pSectionHeader->PointerToRawData), \
        (PDWORD)((DWORD)pImageBuffer + pSectionHeader->VirtualAddress), \
        pSectionHeader->SizeOfRawData);

    //��������
    *pNewBuffer = pTempMergeSection;
    pTempMergeSection = NULL;
    return pOptionHeader->SizeOfImage;
}

//ImageBuffer ---> NewBuffer
//���������ص��ڴ��ImageBuffer���뵽NewBuffer���棬Ȼ��׼�����̣�
DWORD CopyImageBufferToNewBuffer(IN LPVOID pImageBuffer, OUT LPVOID* pNewBuffer)
{
    //����󲿷ֲ������Ǹ�����һ���ģ�����Ͳ���׸����
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    LPVOID pTempNewBuffer = NULL;
    DWORD sizeOfFile = 0;
    DWORD numberOfSection = 0;

    if (pImageBuffer == NULL)
    {
        printf("������ָ����Ч\r\n");
    }
    //�ж��Ƿ�����Ч��MZ��־
    if (*((PWORD)pImageBuffer) != IMAGE_DOS_SIGNATURE)
    {
        printf("������Ч��MZͷ\r\n");
        return 0;
    }
    pDosHeader = (PIMAGE_DOS_HEADER)pImageBuffer;
    //�ж��Ƿ�����Ч��PE��־
    if (*((PDWORD)((DWORD)pImageBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("������Ч��PE��־\r\n");
        return 0;
    }
    //NTͷ��ַ
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pImageBuffer + pDosHeader->e_lfanew);
    //��׼PE�ļ�ͷ
    pPEHeader = (PIMAGE_FILE_HEADER)(((DWORD)pNTHeader) + 4);
    //��ѡPEͷ
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
    //��һ���ڱ��ַ
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //�����ļ���Ҫ�Ŀռ�--���һ���ڵ��ļ�ƫ��+�ڶ����ĳ���
    /*
    numberOfSection = pPEHeader->NumberOfSections;
    pSectionHeader = pSectionHeader[numberOfSection-1];
    sizeOfFile = (pSectionHeader->PointerToRawData + pSectionHeader->Misc.VirtualSize + pOptionHeader->FileAlignment);
    printf("sizeOfFile %X \r\n",sizeOfFile);

    for (DWORD i=0;i<=numberOfSection;i++)
    {
        sizeOfFile += sizeOfFile[i];
    }
    */

    sizeOfFile = pOptionHeader->SizeOfHeaders;
    //ʹ��winhex��notepad.exe ��0x00000400�����ǵ�һ����֮ǰ�����д�С
    for (DWORD i = 0; i < pPEHeader->NumberOfSections; i++)
    {
        sizeOfFile += pSectionHeader[i].SizeOfRawData;  // pSectionHeader[i]��һ�ּӷ�
    }

    /*
    �����forѭ�������˼���ǻ��ڼ����ڵ���������ѭ������sizeOfFile��ֵ����ΪSizeOfRawData���ļ��ж����Ĵ�С��
    ����ѭ���������£�
    sizeOfFile = 0x00000400 + 0x00007800 = 0x00007C00
    sizeOfFile = 0x00007C00 + 0x00000800 = 0x00008400
    sizeOfFile = 0x00008400 + 0x00008000 = 0x00010400

    */

    //����SizeOfImage�����µĿռ�
    pTempNewBuffer = malloc(sizeOfFile);

    if (!pTempNewBuffer)
    {
        printf("�����ڴ�ռ�ʧ��\r\n");
        return 0;
    }
    //��ʼ���µĻ�����
    memset(pTempNewBuffer, 0, sizeOfFile);
    //����SizeOfHeaders ��copyͷ
    memcpy(pTempNewBuffer, pDosHeader, pOptionHeader->SizeOfHeaders);
    //���ݽڱ�ѭ�����ƽ�
    //PIMAGE_SECTION_HEADER pTempSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader);
    PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;
    for (int j = 0; j < pPEHeader->NumberOfSections; j++, pTempSectionHeader++)
    {
        /*memcpy((LPVOID)((DWORD)pTempNewBuffer + pTempSectionHeader->PointerToRawData),
        (LPVOID)((DWORD)pImageBuffer + pTempSectionHeader->VirtualAddress),
        pTempSectionHeader->SizeOfRawData);*/
        //PointerToRawData�������ļ��е�ƫ��,VirtualAddress�������ڴ��е�ƫ�Ƶ�ַ,SizeOfRawData�����ļ��ж����ĳߴ�
        memcpy((PDWORD)((DWORD)pTempNewBuffer + pTempSectionHeader->PointerToRawData),
            (PDWORD)((DWORD)pImageBuffer + pTempSectionHeader->VirtualAddress),
            pTempSectionHeader->SizeOfRawData);
        //printf("%X  --> PoniterToRadata\r\n",pTempSectionHeader->PointerToRawData);
        //printf("%X  --> VirtualAddress\r\n",pTempSectionHeader->VirtualAddress);
        //printf("%X  --> VirtualSize\r\n",pTempSectionHeader->Misc.VirtualSize);
    }

    //��������
    *pNewBuffer = pTempNewBuffer;
    pTempNewBuffer = NULL;
    return sizeOfFile;
}

//������õ���MemBuffer���̵����أ�
BOOL MemeryTOFile(IN LPVOID pMemBuffer, IN size_t size, OUT const char* lpszFile)
{
    FILE* fp = NULL;
    fp = fopen(lpszFile, "wb+");
    if (!fp)  //  �����Ҹտ�ʼд©��һ�����ںţ���ɸ���NULL�ˣ����´���
//  if(fp == NULL)  ������ôд��û����
    {
        fclose(fp);
        return FALSE;
    }
    fwrite(pMemBuffer, size, 1, fp);
    fclose(fp);
    fp = NULL;
    return TRUE;
}

//RVA��ʽת��FOA  --- RvaToFileOffset
DWORD RvaToFileOffset(IN LPVOID pFileBuffer, IN DWORD dwRva)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    DWORD numberOfSection = 0;
    DWORD dwFOAValue = 0;

    //�ж�ָ���Ƿ���Ч
    if (!pFileBuffer)
    {
        printf("pFileBuffer ָ����Ч\r\n");
        return 0;
    }
    //�ж��Ƿ�����Ч��MZ��־
    if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
    {
        printf("pFileBuffer������Ч��MZ��־\r\n");
        return 0;
    }
    //�ж��Ƿ���һ����Ч��PE��־
    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    if (*((PWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("pFileBuffer����һ����Ч��PE��־\r\n");
        return 0;
    }

    printf("��ǰ��Rva��ַ: %#X \r\n", dwRva);
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x04);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //�������ʱ�ڱ�ָ���������ļ������
    numberOfSection = pPEHeader->NumberOfSections;
    PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;


    //�ж�dwRva�����Ľ�
    if (dwRva <= pOptionHeader->SizeOfHeaders)
    {
        return (DWORD)dwRva;
    }
    //�������ж����rva��ַ�����Ľ��ڵ�һ����֮ǰ��ôֱ�ӷ���rva�ĵ�ַ��
    //����������ǿ�ʼ�������ҽڣ�
    else
    {
        for (DWORD n = 0; n < numberOfSection; n++, pTempSectionHeader++)
        {//�������ж����ĸ��ڵķ�Χ��Ȼ�����rva���ڵĵ�ַ��ȥ���ڽڵ�VirtualAddress�õ���ƫ��ֵ�����ļ��ж�Ӧ�ڵ�ƫ��ֵPointerToRawData
            if ((dwRva >= pTempSectionHeader->VirtualAddress) && (dwRva < pTempSectionHeader->VirtualAddress + pTempSectionHeader->Misc.VirtualSize))
            {
                dwFOAValue = dwRva - pTempSectionHeader->VirtualAddress + pTempSectionHeader->PointerToRawData;
            }
            else
            {
                printf("RvaToFoa ת��ʧ�ܣ�\r\n");
                return 0;
            }
        }
    }
    return dwFOAValue;
}

//FOA��ʽת��RVA  --- ImageOffset
DWORD FoaToImageOffset(IN LPVOID pFileBuffer, IN DWORD dwFoa)
{
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_NT_HEADERS pNTHeader = NULL;
    PIMAGE_FILE_HEADER pPEHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    DWORD numberOfSection = 0;
    DWORD dwRVAValue = 0;

    //�ж�ָ���Ƿ���Ч
    if (!pFileBuffer)
    {
        printf("pFileBuffer ָ����Ч\r\n");
        return 0;
    }
    //�ж��Ƿ�����Ч��MZ��־
    if (*((PWORD)pFileBuffer) != IMAGE_DOS_SIGNATURE)
    {
        printf("pFileBuffer������Ч��MZ��־\r\n");
        return 0;
    }
    //�ж��Ƿ���һ����Ч��PE��־
    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer;
    if (*((PWORD)((DWORD)pFileBuffer + pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
    {
        printf("pFileBuffer����һ����Ч��PE��־\r\n");
        return 0;
    }

    printf("��ǰ��Foa��ַ: %#X \r\n", dwFoa);
    pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pFileBuffer + pDosHeader->e_lfanew);
    pPEHeader = (PIMAGE_FILE_HEADER)((DWORD)pNTHeader + 0x04);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((DWORD)pPEHeader + IMAGE_SIZEOF_FILE_HEADER);
    pSectionHeader = (PIMAGE_SECTION_HEADER)((DWORD)pOptionHeader + pPEHeader->SizeOfOptionalHeader);

    //�������ʱ�ڱ�ָ���������ļ������
    numberOfSection = pPEHeader->NumberOfSections;
    PIMAGE_SECTION_HEADER pTempSectionHeader = pSectionHeader;

    if (dwFoa <= pOptionHeader->SizeOfHeaders)
    {
        return (DWORD)dwFoa;
    }
    else
    {
        for (DWORD n = 0; n < numberOfSection; n++, pTempSectionHeader++)
        {
            if ((dwFoa >= pTempSectionHeader->PointerToRawData) && (dwFoa < pTempSectionHeader->SizeOfRawData))
            {
                dwRVAValue = dwFoa - pTempSectionHeader->PointerToRawData + pTempSectionHeader->VirtualAddress;
            }
            else
            {
                printf("FoaToRva ת��ʧ�ܣ�\r\n");
                return 0;
            }
        }
    }
    return dwRVAValue;
}

//��ԭ�е�exe�ļ��п�ʼ�������ShellCode���룻

VOID AddCodeInCodeSec()
{
    LPVOID pFileBuffer = NULL;
    LPVOID pImageBuffer = NULL;
    LPVOID pNewBuffer = NULL;
    PIMAGE_DOS_HEADER pDosHeader = NULL;
    PIMAGE_FILE_HEADER pFileHeader = NULL;
    PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;
    PIMAGE_SECTION_HEADER pSectionHeader = NULL;
    PBYTE codeBegin = NULL;
    BOOL isOK = FALSE;
    DWORD size = 0;

    //File-->FileBuffer
    ReadPEFile((LPSTR)FilePath_In, &pFileBuffer);
    if (!pFileBuffer)
    {
        printf("�ļ�-->������ʧ��\r\n");
        return;
    }

    //FileBuffer-->ImageBuffer
    CopyFileBufferToImageBuffer(pFileBuffer, &pImageBuffer);
    if (!pImageBuffer)
    {
        printf("FileBuffer-->ImageBufferʧ��\r\n");
        free(pFileBuffer);
        return;
    }

    //�жϴ���ο��������Ƿ��ܹ��㹻�洢ShellCode����
    pDosHeader = (PIMAGE_DOS_HEADER)pImageBuffer;
    pFileHeader = (PIMAGE_FILE_HEADER)(((DWORD)pImageBuffer + pDosHeader->e_lfanew) + 4);
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)(((DWORD)pImageBuffer + pDosHeader->e_lfanew) + 4 + IMAGE_SIZEOF_FILE_HEADER);
    pSectionHeader = (PIMAGE_SECTION_HEADER)(((DWORD)pImageBuffer + pDosHeader->e_lfanew) + 4 + IMAGE_SIZEOF_FILE_HEADER + pFileHeader->SizeOfOptionalHeader);
    if (((pSectionHeader->SizeOfRawData) - (pSectionHeader->Misc.VirtualSize)) < SHELLCODELENGTH)
    {
        printf("����������пռ䲻��\r\n");
        free(pFileBuffer);
        free(pImageBuffer);
    }

    //�����븴�Ƶ���������
    codeBegin = (PBYTE)((DWORD)pImageBuffer + pSectionHeader->VirtualAddress + pSectionHeader->Misc.VirtualSize);
    printf("pSectionHeader->VirtualAddress: %#010X\r\n", pSectionHeader->VirtualAddress);
    printf("pSectionHeader->Misc.VirtualSize: %#010X\r\n", pSectionHeader->Misc.VirtualSize);
    printf("codeBegin: %#010X\r\n", codeBegin);

    memcpy(codeBegin, ShellCode, SHELLCODELENGTH);

    //����E8-->call����Ĵ�������
    DWORD callAddr = (MESSAGEBOXADDR - (pOptionHeader->ImageBase + ((DWORD)(codeBegin + 0xD) - (DWORD)pImageBuffer)));
    printf("callAddr ---> %#010X \r\n", callAddr);
    *(PDWORD)(codeBegin + 0x09) = callAddr;
    printf("*(PWORD)(codeBegin + 0x09) ---> %#010X \r\n", *(PDWORD)(codeBegin + 0x09));
    /*
    ��������E8����⣬��ʽ��X = Ҫ��ת�ĵ�ַ - (E8��ǰ�ĵ�ַ + 5)��
    Ҫ��ת�ĵ�ַ����������ӹ���ɵģ���������Ҫ�������MessageBox�ĵ�ַ��
    Ȼ��Ҫ��ȥE8��ǰ�ĵ�ַ+5��λ�ã����ﲻ��̫����⣻
    ���ǵ�Ŀ����Ҫ��E8�����4���ֽڼ��������Ȼ��д�뵽E8���棬Ҳ���ǹ�ʽ��X��
    ���湫ʽE8��ǰ��ַ+5 �����ڴ����Ҫ��λ�����λ�þ�Ҫ�Ӵ����Dos��ʼͨ��ָ����ӣ�
    ����λ��ƫ�Ƶ�E8��ǰ��ַ+5��λ�ã�
    ���Զ�λcodeBegin��λ���ǣ�pImageBufferָ���ʼ��λ�ã�Dosͷλ�ã�ͨ���ڴ���ƫ�ƵĿ���ƶ�����һ���ڱ��λ�ã�
    Ҳ���������pSectionHeader->VirtualAddress ������ʽ��
    Ȼ����ƫ�Ƶ�һ���ڱ����ڴ��ж���ǰʵ�ʵĿ�ȣ��ߴ磩pSectionHeader->Misc.VirtualSize��
    ����һ������֮��͵��˵�һ���ڱ�û�ж���ǰ��λ�ã����λ�þ������ǿ������ShellCode�������ʼλ�ã�
    �������ShellCode�������ʼλ��֮�󣬾�Ҫ��취���E8λ�ú����4���ֽڣ���ʱ����ShellCode����Ŀ�ȣ�
    ���м��㣬ȷ��0x6A 00 0x6A 00 0x6A 00 0x6A 00 E8 00 00 00 00 �պ��������13��λ�ã�����ʮ�����ƿ���
    ����0xD��������codeBeginƫ��0xD��λ�ü��ɵ���E9��λ�ã���Ҳ��������˵��(E8��ǰ�ĵ�ַ + 5);
    ���������λ��֮������������������Ҫ�ڳ�������֮�����ڴ������ShellCode���룻��������һ��Ҫ�������
    ��׼ȷ��ƫ�Ƶ�ַ������������ô���쵽�ĸ�λ�ã�����׼ȷ�ҵ�λ�ã�
    ע�⣺������Ҫע��һ����⣬����˵��pImageBuffer��������Ǽ��س�������������ڴ��У������ǳ����ڣ�
    �����е��Ǹ��ڴ棬����һ��Ҫ�������������ǲ�һ���ģ�����������������������ΪʲôҪ��ȥDosͷ�ģ�
    �׵�ַ��(DWORD)(codeBegin + 0xD) - (DWORD)pImageBuffer)
    */

    //����E9-->jmp����Ĵ�������
    DWORD jmpAddr = ((pOptionHeader->ImageBase + pOptionHeader->AddressOfEntryPoint) - (pOptionHeader->ImageBase + ((DWORD)(codeBegin + SHELLCODELENGTH) - (DWORD)pImageBuffer)));
    printf("jmpAddr ---> %#010X \r\n", jmpAddr);
    *(PDWORD)(codeBegin + 0x0E) = jmpAddr;
    printf("*(PWORD)(codeBegin + 0x0E) ---> %#010X \r\n", *(PDWORD)(codeBegin + 0x0E));
    /*
    ��ʽ��X = Ҫ��ת�ĵ�ַ - (E9��ǰ�ĵ�ַ + 5)
    ����ͬ����Ҫ�����E9����4���ֽڵĵ�ַ�����ǵ�Ŀ�������������OEP�ĵ�ַ������ִ�����MessageBox֮����ת��
    OEP�ĵ�ַ����ô�����Ҫ�ȼ����OEP��ַ������pOptionHeader->ImageBase + pOptionHeader->AddressOfEntryPoint��
    �ټ�ȥ(E9��ǰ�ĵ�ַ + 5) 0x6A 00 0x6A 00 0x6A 00 0x6A 00 E8 00 00 00 00 E9 00 00 00 00��
    (DWORD)codeBegin + SHELLCODELENGTH ���Ǽ���ShellCode�ܳ��ȣ�ƫ�����֮���ȥImageBuffer�׵�ַ�ټ���ImageBase��
    */

    //����OEP
    printf("pOptionHeader->AddressOfEntryPoint ---> %#010X \r\n", pOptionHeader->AddressOfEntryPoint);
    printf("(DWORD)codeBegin ---> %#010X \r\n", ((DWORD)codeBegin - (DWORD)pImageBuffer));
    pOptionHeader->AddressOfEntryPoint = (DWORD)codeBegin - (DWORD)pImageBuffer;
    printf("pOptionHeader->AddressOfEntryPoint ---> %#010X \r\n", pOptionHeader->AddressOfEntryPoint);
    //����OEP����⣬���Ƕ�λ��OEP��ַ��Ȼ��ֱ��ͨ��codeBegin��ַ��ȥpImageBuffer���׵�ַ���ɣ�

    //ImageBuffer-->NewBuffer
    size = CopyImageBufferToNewBuffer(pImageBuffer, &pNewBuffer);
    if (size == 0 || !pNewBuffer)
    {
        printf("ImageBuffer-->NewBufferʧ��\r\n");
        free(pFileBuffer);
        free(pImageBuffer);
        return;
    }

    //NewBuffer-->�ļ�
    isOK = MemeryTOFile(pNewBuffer, size, FilePath_Out);
    if (isOK)
    {
        printf("�޸Ĵ������SHELLCODE ���̳ɹ�\r\n");
        return;
    }

    //�ͷ��ڴ�
    free(pFileBuffer);
    free(pImageBuffer);
    free(pNewBuffer);
}

//���ú��������ڱ�ͽڲ������ɹ�֮�󲢴��̵����أ�
VOID NewSectionsInCodeSec()
{
    LPVOID pFileBuffer = NULL;
    LPVOID pNewImageBuffer = NULL;
    BOOL isOK = FALSE;
    DWORD size1 = 0;
    DWORD size2 = 0;

    //File-->FileBuffer
    size1 = ReadPEFile(FilePath_In, &pFileBuffer);
    if (size1 == 0 || !pFileBuffer)
    {
        printf("�ļ�-->������ʧ��\r\n");
        return;
    }
    printf("fileSize - Final: %#X \r\n", size1);

    //FileBuffer-->NewImageBuffer
    size2 = CopyFileBufferToNewImageBuffer(pFileBuffer, size1, &pNewImageBuffer);
    if (size2 == 0 || !pFileBuffer)
    {
        printf("FileBuffer-->NewImageBufferʧ��\r\n");
        free(pFileBuffer);
        return;
    }
    printf("sizeOfFile - Final: %#X \r\n", size2);
    //NewImageBuffer-->�ļ�
    isOK = MemeryTOFile(pNewImageBuffer, size2, FilePath_Out);
    if (isOK)
    {
        printf("�����ڱ�ͽڴ��̳ɹ�\r\n");
        return;
    }

    //�ͷ��ڴ�
    free(pFileBuffer);
    free(pNewImageBuffer);
}

//���ú�������һ����
VOID ExtendLastSectionsInCodeSec()
{
    //ReadPEFile CopyFileBufferToImageBuffer CopyImageBufferToNewImageBuffer

    LPVOID pFileBuffer = NULL;
    LPVOID pImageBuffer = NULL;
    LPVOID pNewImageBuffer = NULL;
    BOOL isOK = FALSE;
    DWORD FileBufferSize = 0;
    DWORD ImageBufferSize = 0;
    DWORD size = 0;

    //File-->FileBuffer
    FileBufferSize = ReadPEFile(FilePath_In, &pFileBuffer);
    if (FileBufferSize == 0 || !pFileBuffer)
    {
        printf("�ļ�-->������ʧ��\r\n");
        return;
    }
    printf("FileBufferSize - Final: %#X \r\n", FileBufferSize);

    //FileBuffer-->ImageBuffer
    ImageBufferSize = FileBufferToModifyImageBuffer(pFileBuffer, &pImageBuffer);
    if (ImageBufferSize == 0 || !pFileBuffer)
    {
        printf("FileBuffer-->ImageBufferʧ��\r\n");
        free(pFileBuffer);
        return;
    }
    printf("ImageBufferSize - Final: %#X \r\n", ImageBufferSize);

    size = CopyImageBufferToNewBuffer(pImageBuffer, &pNewImageBuffer);
    if (size == 0 || !pImageBuffer)
    {
        printf("pImageBuffer-->pNewImageBufferʧ��\r\n");
        free(pFileBuffer);
        return;
    }
    //pNewImageBuffer-->�ļ�
    isOK = MemeryTOFile(pNewImageBuffer, size, FilePath_Out);
    if (isOK)
    {
        printf("����һ���ڳɹ���������\r\n");
        return;
    }

    //�ͷ��ڴ�
    free(pFileBuffer);
    free(pImageBuffer);
    free(pNewImageBuffer);
}


//���ú�������һ����
VOID ModifySectionsOneInCodeSec()
{
    //ReadPEFile CopyFileBufferToImageBuffer FileBufferToModifyOneImageBuffer MemeryTOFile

    LPVOID pFileBuffer = NULL;
    LPVOID pImageBuffer = NULL;
    LPVOID pNewImageBuffer = NULL;
    BOOL isOK = FALSE;
    DWORD FileBufferSize = 0;
    DWORD ImageBufferSize = 0;
    DWORD size = 0;

    //File-->FileBuffer
    FileBufferSize = ReadPEFile(FilePath_In, &pFileBuffer);
    if (FileBufferSize == 0 || !pFileBuffer)
    {
        printf("�ļ�-->������ʧ��\r\n");
        return;
    }
    printf("FileBufferSize ---> %#X \r\n", FileBufferSize);

    //FileBuffer-->ImageBuffer
    ImageBufferSize = CopyFileBufferToImageBuffer(pFileBuffer, &pImageBuffer);
    if (ImageBufferSize == 0 || !pFileBuffer)
    {
        printf("FileBuffer-->ImageBufferʧ��\r\n");
        free(pFileBuffer);
        return;
    }
    printf("ImageBufferSize ---> %#X \r\n", ImageBufferSize);

    size = ImageBufferMergeSections(pImageBuffer, &pNewImageBuffer);
    if (size == 0 || !pImageBuffer)
    {
        printf("pImageBuffer-->pNewImageBufferʧ��\r\n");
        free(pFileBuffer);
        return;
    }
    //pNewImageBuffer-->�ļ�
    isOK = MemeryTOFile(pNewImageBuffer, size, FilePath_Out);
    if (isOK)
    {
        printf("�ϲ�����ɣ����̳ɹ�\r\n");
        return;
    }

    //�ͷ��ڴ�
    free(pFileBuffer);
    free(pImageBuffer);
    free(pNewImageBuffer);
}

VOID RvaAndFoaConversion()
{
    LPVOID pFileBuffer = NULL;
    DWORD FileBufferSize = 0;
    DWORD FoaFinalVaule = 0;
    DWORD RvaFinalVaule = 0;
    size_t pRVA = 1180;
    size_t pFOA = 2279;

    //File-->FileBuffer
    FileBufferSize = ReadPEFile(FilePath_In, &pFileBuffer);
    if (FileBufferSize == 0 || !pFileBuffer)
    {
        printf("�ļ�-->������ʧ��\r\n");
        return;
    }
    printf("FileBufferSize: %#X \r\n", FileBufferSize);

    FoaFinalVaule = RvaToFileOffset(pFileBuffer, pRVA);
    if (FoaFinalVaule == 0 || !pFileBuffer)
    {
        printf("pFileBuffer-->��ȡʧ��\r\n");
        free(pFileBuffer);
        return;
    }
    printf("ת���ɹ� --> FoaFinalVaule ��������pRVAֵ: : %#X %#X\r\n", FoaFinalVaule, pRVA);

    RvaFinalVaule = FoaToImageOffset(pFileBuffer, pFOA);
    if (RvaFinalVaule == 0 || !pFileBuffer)
    {
        printf("pFileBuffer-->��ȡʧ��\r\n");
        free(pFileBuffer);
        return;
    }
    printf("ת���ɹ� --> RvaFinalVaule ��������pFOAֵ : %#X %#X\r\n", RvaFinalVaule, pFOA);


    free(pFileBuffer);
}

// allpelx.cpp : Defines the entry point for the console application.
//


