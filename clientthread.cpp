#include "clientthread.h"

ClientThread::ClientThread(int h, QObject *parent) :
        QThread(parent),client(parent) /*s(QAbstractSocket::TcpSocket, parent)*//*, file(parent)*/
{
        blockSize = 0;
        blockNumber  = 0;
        client.setSocketDescriptor(h);
        connect(&client, SIGNAL(readyRead()), this, SLOT(getSignalFromClient()));
        connect(&client, SIGNAL(bytesWritten(qint64)), this, SIGNAL(bytesSent(qint64)));
        isCanceled = false;
        indexOfEntry = 0;
        isFileSelected = false;
        isFolderSelected = false;
}
void ClientThread::run()
{
    exec();
}
void ClientThread::setFilePath(QString f)
{
    filePath = f;
    filePath.append("/");
    fileFilters << "*.tif" << "*.ppf" << "*.ink";
    folderFilters << "*";
}
void ClientThread::getSignalFromClient()
{
    if (client.bytesAvailable() < 1)
        return;
    QByteArray data = client.read(5);
    qint64 size;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    char *d = data.data();
    if (d[0] == 'f' || d[0] == 'd'){  //client is asking for all the entry names in image folder
        isCanceled = false;
        QDir imageDir(filePath);
        fileNames = imageDir.entryList(fileFilters, QDir::Files);
        folderNames = imageDir.entryList(folderFilters, QDir::Dirs);
        folderNames.removeAt(folderNames.indexOf("."));
        folderNames.removeAt(folderNames.indexOf(".."));
        for (int i = 0; i < folderNames.length(); i ++){
            block.clear();
            out.device()->seek(0);
            out << qint16(0x0000) << folderNames.at(i).toUtf8();
            size = block.size();
            client.write((char*)&size, sizeof(qint64));
            client.write(block.data(), size);
            if(!client.waitForBytesWritten(-1)){
                emit error(3);
                return;
            }
        }
        for (int i = 0; i < fileNames.length(); i ++){
            block.clear();
            out.device()->seek(0);
            out << qint16(0x0000) << fileNames.at(i).toUtf8();
            size = block.size();
            client.write((char*)&size, sizeof(qint64));
            client.write(block.data(), size);
            if(!client.waitForBytesWritten(-1)){
                emit error(3);
                return;
            }
        }
        //send file name
        block.clear();
        out.device()->seek(0);
        if (d[0] == 'f')
            out << qint16(0x000A);
        else if (d[0] == 'd')
            out << qint16(0x000B);
        size = block.size();
        client.write((char*)&size, sizeof(qint64));
        client.write(block.data(), size);
        if(!client.waitForBytesWritten(-1)){
            emit error(3);
            return;
        }
    }
    else if (d[0] == 't' || d[0] == 'r'){  //client has selected an entry in image folder and asks server to transmit that entry
        numberOfBytesToBeTransmit = 0;
        numberOfFilesSent = 0;
        indexOfEntry = d[1] + (d[2] << 8) + (d[3] << 16) + (d[4] << 24);

        if (d[0] == 't'){
            if (indexOfEntry < folderNames.length()){ //entry selected is a folder
                imageFolderPath = folderNames.at(indexOfEntry);
                imageFolderPath.prepend(filePath);
                imageFolderPath.append("/");
                QDir dir(imageFolderPath);
                QStringList nameFilters;
                nameFilters << "*.tif" << "*.ppf";
                QStringList filesInFolder = dir.entryList(nameFilters, QDir::Files);
                //send file quantity
                block.clear();
                out.device()->seek(0);
                QString fileQuantity;
                fileQuantity.setNum(filesInFolder.length());
                out << qint16(0x0001) << fileQuantity.toUtf8();
                size = block.size();
                client.write((char*)&size, sizeof(qint64));
                client.write(block.data(), size);
                if(!client.waitForBytesWritten(-1)){
                    emit error(3);
                    return;
                }
                numberOfFilesToBeTransmit = filesInFolder.length();
                isFileSelected = false;
                isFolderSelected = true;
                for (int i = 0; i < filesInFolder.length(); i ++){
                    QString fp = filesInFolder.at(i);
                    fp.prepend(imageFolderPath);
                    QFile f(fp);
                    numberOfBytesToBeTransmit += f.size();
                }
                emit progressRange(numberOfBytesToBeTransmit);
            }
            else if (indexOfEntry < (folderNames.length() + fileNames.length())){       //entry selected is a single file
                imageFilePath = fileNames.at(indexOfEntry - folderNames.length());
                imageFilePath.prepend(filePath);

                //send file quantity
                block.clear();
                out.device()->seek(0);
                QString fileQuantity;
                fileQuantity.setNum(1);
                out << qint16(0x0001) << fileQuantity.toUtf8();
                size = block.size();
                client.write((char*)&size, sizeof(qint64));
                client.write(block.data(), size);
                if(!client.waitForBytesWritten(-1)){
                    emit error(3);
                    return;
                }
                numberOfFilesToBeTransmit = 1;
                isFileSelected = true;
                isFolderSelected = false;

                QString fp = imageFilePath;
                QFile f(fp);
                numberOfBytesToBeTransmit = f.size();
                emit progressRange(numberOfBytesToBeTransmit);
            }
        }
        else if (d[0] == 'r'){
            if (indexOfEntry < folderNames.length() && (indexOfEntry >= 0)){
                QString pathOfTheFolderToDelete = filePath + folderNames.at(indexOfEntry);
                pathOfTheFolderToDelete = pathOfTheFolderToDelete.replace('/', '\\');
                char str[100];
                QByteArray tempString1 = pathOfTheFolderToDelete.toAscii();
                const char *tempString2 = tempString1.data();
                sprintf(str, "rd/s/q %s", tempString2);
                system(str);
            }
            else if (indexOfEntry < (folderNames.length() + fileNames.length()) && (indexOfEntry >= 0)){
                QString pathOfTheFileToDelete = filePath + fileNames.at(indexOfEntry - folderNames.length());
                QFile fileToDelete(pathOfTheFileToDelete);
                fileToDelete.remove();
            }
            else{   //DELETE ALL FILES!!!
                qDebug() << "DELETING ALL FILES!!!" << d[1] << d[2] << d[3] << d[4];
                for (int i = 0; i < (folderNames.length() + fileNames.length()); i ++){
                    if (i < folderNames.length()){          //delete all the folders
                        QString pathOfTheFolderToDelete = filePath + folderNames.at(i);
                        pathOfTheFolderToDelete = pathOfTheFolderToDelete.replace('/', '\\');
                        char str[100];
                        QByteArray tempString1 = pathOfTheFolderToDelete.toAscii();
                        const char *tempString2 = tempString1.data();
                        sprintf(str, "rd/s/q %s", tempString2);
                        system(str);
                    }
                    else{                                   //delete all the files
                        QString pathOfTheFileToDelete = filePath + fileNames.at(i - folderNames.length());
                        QFile fileToDelete(pathOfTheFileToDelete);
                        fileToDelete.remove();
                    }
                }
            }
        }
    }
    else if (d[0] == 'e'){  //errors,could be more than 6 color files or file size too big
        emit bytesSent(0);
        emit progressRange(10000);
        return;
    }
    else if (d[0] == 'n'){  //send file name and size
        if (isFolderSelected){  //sending folder
            QDir dir(imageFolderPath);
            QStringList nameFilters;
            nameFilters << "*.tif" << "*.ppf";
            QStringList filesInFolder = dir.entryList(nameFilters, QDir::Files);
            if (numberOfFilesSent < numberOfFilesToBeTransmit){
                QString fileName, fileSize;

                //send file name
                block.clear();
                out.device()->seek(0);
                out << qint16(0x0002) << filesInFolder.at(numberOfFilesSent).toUtf8();
                size = block.size();
                client.write((char*)&size, sizeof(qint64));
                client.write(block.data(), size);

                if(!client.waitForBytesWritten(-1)){
                    emit error(3);
                    return;
                }

                //send file size
                block.clear();
                out.device()->seek(0);
                fileName = imageFolderPath;
                fileName.append(filesInFolder.at(numberOfFilesSent));
                QFile imageFile(fileName);
                fileSize = fileSize.setNum(imageFile.size());
                out << qint16(0x0003) << fileSize.toUtf8();
                size = block.size();
                client.write((char*)&size, sizeof(qint64));
                client.write(block.data(), size);

                if(!client.waitForBytesWritten(-1)){
                    emit error(3);
                    return;
                }
            }
        }
        else{       //sending single file
            if (numberOfFilesSent < numberOfFilesToBeTransmit){
                QString fileName, fileSize;
                QFile imageFile(imageFilePath);
                fileName = imageFilePath.right(imageFilePath.length() - imageFilePath.lastIndexOf("/") - 1);
                //send file name
                block.clear();
                out.device()->seek(0);
                out << qint16(0x0002) << fileName.toUtf8();
                size = block.size();
                client.write((char*)&size, sizeof(qint64));
                client.write(block.data(), size);

                if(!client.waitForBytesWritten(-1)){
                    emit error(3);
                    return;
                }

                //send file size
                block.clear();
                out.device()->seek(0);
                fileSize = fileSize.setNum(imageFile.size());
                out << qint16(0x0003) << fileSize.toUtf8();
                size = block.size();
                client.write((char*)&size, sizeof(qint64));
                client.write(block.data(), size);

                if(!client.waitForBytesWritten(-1)){
                    emit error(3);
                    return;
                }
            }
        }
    }
    else if (d[0] == 'g'){
        if (isFolderSelected){  //sending folder
            QDir dir(imageFolderPath);
            QStringList nameFilters;
            nameFilters << "*.tif" << "*.ppf";
            QStringList filesInFolder = dir.entryList(nameFilters, QDir::Files);
            if (numberOfFilesSent < numberOfFilesToBeTransmit){
                QString fileName = imageFolderPath;
                fileName.append(filesInFolder.at(numberOfFilesSent));
                QFile imageFile(fileName);

                imageFile.open(QIODevice::ReadWrite);
                //send file content
                do{
                    qApp->processEvents();
                    if (!isCanceled){
                        block.clear();
                        out.device()->seek(0);
                        out << qint16(0x0004) << imageFile.read(0xFFF0);
                        size = block.size();

                        client.write((char*)&size, sizeof(qint64));
                        client.write(block.data(), size);
                        if(!client.waitForBytesWritten(-1)){
                            emit error(3);
                        }
                    }
                    else{
                        block.clear();
                        out.device()->seek(0);
                        out << qint16(0x0006);
                        size = block.size();

                        client.write((char*)&size, sizeof(qint64));
                        client.write(block.data(), size);
                        if(!client.waitForBytesWritten(-1)){
                            emit error(3);
                        }
                        emit status(6);
                        return;
                    }
                } while(!imageFile.atEnd() && (!isCanceled));
                //send file EOF
                block.clear();
                out.device()->seek(0);
                out << qint16(0x0005);
                size = block.size();
                client.write((char*)&size, sizeof(qint64));
                client.write(block.data(), size);
                if(!client.waitForBytesWritten(-1))
                    emit error(3);
                emit status(3);
                imageFile.close();

                numberOfFilesSent ++;
            }
        }
        else{
            if (numberOfFilesSent < numberOfFilesToBeTransmit){
                QString fileName;
                QFile imageFile(imageFilePath);
                fileName = imageFilePath.right(imageFilePath.length() - imageFilePath.lastIndexOf("/") - 1);

                imageFile.open(QIODevice::ReadWrite);
                //send file content
                do{
                    if (!isCanceled){
                        block.clear();
                        out.device()->seek(0);
                        out << qint16(0x0004) << imageFile.read(0xFFF0);
                        size = block.size();

                        client.write((char*)&size, sizeof(qint64));
                        client.write(block.data(), size);
                        if(!client.waitForBytesWritten(-1)){
                            emit error(3);
                        }
                    }
                    else{
                        block.clear();
                        out.device()->seek(0);
                        out << qint16(0x0006);
                        size = block.size();

                        client.write((char*)&size, sizeof(qint64));
                        client.write(block.data(), size);
                        if(!client.waitForBytesWritten(-1))
                            emit error(3);
                        emit status(6);
                        return;
                    }
                } while(!imageFile.atEnd() && (!isCanceled));
                //send file EOF
                block.clear();
                out.device()->seek(0);
                out << qint16(0x0005);
                size = block.size();

                client.write((char*)&size, sizeof(qint64));
                client.write(block.data(), size);
                if(!client.waitForBytesWritten(-1))
                    emit error(3);
                emit status(3);
                imageFile.close();
                numberOfFilesSent ++;
            }
        }
    }
}
