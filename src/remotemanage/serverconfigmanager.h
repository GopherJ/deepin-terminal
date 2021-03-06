#ifndef SERVERCONFIGMANAGER_H
#define SERVERCONFIGMANAGER_H

#include <QList>
#include <QMap>
#include <QObject>
#include <QDir>
#include <QSettings>
#include <QStandardPaths>
#include <QMutex>

struct ServerConfig {
    QString m_serverName;
    QString m_address;
    QString m_userName;
    QString m_password;
    QString m_privateKey;
    QString m_port;
    QString m_group;
    QString m_path;
    QString m_command;
    QString m_encoding;
    QString m_backspaceKey;
    QString m_deleteKey;
};

class ServerConfigOptDlg;
class ServerConfigManager : public QObject
{
    Q_OBJECT
public:
    static ServerConfigManager *instance();
    void initServerConfig();
    void saveServerConfig(ServerConfig *config);
    void delServerConfig(ServerConfig *config);
    void modifyServerConfig(ServerConfig *newConfig, ServerConfig *oldConfig);
    QMap<QString, QList<ServerConfig *>> &getServerConfigs();

    // 添加修改弹窗
    void setModifyDialog(QString key, ServerConfigOptDlg *dlg);
    // 删除弹窗
    void removeDialog(ServerConfigOptDlg *dlg);
    // 同步弹窗数据
    void SyncData(QString key, ServerConfig *newConfig);
    // 删除数据，关闭所有同类弹窗
    void closeAllDialog(QString key);

signals:
    void refreshList(QString serverName);

private:
    ServerConfigManager(QObject *parent = nullptr);

private:
    static ServerConfigManager *m_instance;
    // QList<ServerConfig *> m_serverConfigs;
    // 配置文件数据
    QMap<QString, QList<ServerConfig *>> m_serverConfigs;
    // 展示的弹窗的键值及弹窗的指针 <服务器名，同类服务器弹窗列表> 弹窗只需存储修改弹窗
    QMap<QString, QList<ServerConfigOptDlg *>> m_serverConfigDialogMap;


    inline void settServerConfig(QSettings &commandsSettings, const QString &strGroupName, ServerConfig *config);
};

typedef QMap<QString, QList<ServerConfigOptDlg *>>::Iterator serverConfigDialogMapIterator;

#endif  // SERVERCONFIGMANAGER_H
